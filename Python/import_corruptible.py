import sys
import os
import unreal

sys.path.append(os.path.dirname(__file__))
import importing_util

import importlib
importlib.reload(importing_util)

def do_full_import(fbx_path: str, output_folder_path: str) -> tuple[bool, str]:
    success : bool
    imported_path : str
    success, imported_path = importing_util.import_static_mesh(
        fbx_path,
        output_folder_path,
        unreal.Paths.get_base_filename(fbx_path))

    if not success:
        print("Failed to import static mesh!")
        return False, imported_path

    success = importing_util.try_set_materials(imported_path)
    if not success:
        print("Failed to set materials!")
        return False, imported_path

    return True, imported_path


def delete(path : str):
    if unreal.EditorAssetLibrary.does_asset_exist(path):
        unreal.EditorAssetLibrary.delete_asset(path)



def main():
    args = sys.argv[1:]

    clean_fbx_path = args[0]
    tainted_fbx_path = args[1]
    corrupted_fbx_path = args[2]
    output_folder_path = args[3]

    success_clean, clean_imported_path = do_full_import(clean_fbx_path, output_folder_path)
    success_tainted, tainted_imported_path = do_full_import(tainted_fbx_path, output_folder_path)
    success_corrupted, corrupted_imported_path = do_full_import(corrupted_fbx_path, output_folder_path)

    any_fail: bool = not success_clean or not success_tainted or not success_corrupted
    if any_fail:
        delete(clean_imported_path)
        delete(tainted_imported_path)
        delete(corrupted_imported_path)


main()
