import sys
import os
import unreal

sys.path.append(os.path.dirname(__file__))
import importing_util

def main():
    args = sys.argv[1:]

    input_fbx_path = args[0]
    output_folder_path = args[1]

    success : bool
    imported_path : str
    success, imported_path = importing_util.import_static_mesh(
        input_fbx_path,
        output_folder_path,
        unreal.Paths.get_base_filename(input_fbx_path))

    if not success:
        print("Failed to import static mesh!")
        return

    success = importing_util.try_set_materials(imported_path)
    if not success:
        print("Failed to set materials!")
        unreal.EditorAssetLibrary.delete_asset(imported_path)
        return


main()
