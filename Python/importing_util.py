import os
import unreal

def gather_material_instances() -> dict[str, unreal.AssetData]:
    registry = unreal.AssetRegistryHelpers.get_asset_registry()
    path: unreal.TopLevelAssetPath = unreal.TopLevelAssetPath("/Script/Engine", "MaterialInstanceConstant")
    assets: list[unreal.AssetData] = registry.get_assets_by_class(path)
    assets = [a for a in assets if str(a.package_path).startswith("/Game")]
    assets = [a for a in assets if str(a.asset_name).startswith("MI_")]

    dict_out: dict[str, unreal.AssetData] = {}

    for asset in assets:
        name: str = str(asset.asset_name).removeprefix("MI_")
        dict_out[name] = asset

    return dict_out


def import_static_mesh(input_fbx_path: str, output_folder_path: str, new_file_name: str) -> tuple[bool, str]:
    out_asset_path = os.path.join(output_folder_path + "/" + new_file_name + "." + new_file_name)

    if unreal.load_asset(out_asset_path) is not None:
        print(f"Asset at {out_asset_path} already exists!")
        return False, out_asset_path

    # Create import task
    task = unreal.AssetImportTask()
    task.filename = input_fbx_path
    task.destination_path = output_folder_path
    task.destination_name = new_file_name
    task.automated = True
    task.save = True

    # import options for static mesh
    options = unreal.FbxImportUI()
    options.import_mesh = True
    options.static_mesh_import_data = unreal.FbxStaticMeshImportData()
    options.static_mesh_import_data.combine_meshes = True
    options.import_materials = False

    task.options = options

    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])

    if len(task.imported_object_paths) == 0 or task.imported_object_paths[0] == "":
        return False, out_asset_path

    return True, task.imported_object_paths[0]


def try_set_materials(static_mesh_path : str) -> bool:
    static_mesh = unreal.load_asset(static_mesh_path)
    if not isinstance(static_mesh, unreal.StaticMesh):
        print("Static mesh is not a static mesh for some reason?")
        return

    slots: list[unreal.StaticMaterial] = static_mesh.get_editor_property("static_materials")  # TArray<FStaticMaterial>
    materials: dict[str, unreal.MaterialInstanceConstant] = gather_material_instances()

    any_slots_not_found : bool = False

    for i, slot in enumerate(slots):
        slot_name : str = str(slot.material_slot_name)
        if slot_name not in materials:
            print(f"Your slot {slot_name} has no associated material MI_{slot_name} in the project!")
            any_slots_not_found = True
            continue

        new_mat_data : unreal.AssetData = materials[slot_name]
        static_mesh.set_material(i, new_mat_data.get_asset())

    if any_slots_not_found:
        return False

    return True
