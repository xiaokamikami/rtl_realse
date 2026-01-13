#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Scan RTL files in the current directory and subdirectories.
Finds all .sv and .v files and writes their relative paths to config.yaml file.
"""

import os
import glob

def find_sv_v_files(directory='.'):
    """
    Find all .sv and .v files in the specified directory
    """
    svh_files = glob.glob(os.path.join(directory, '**', '*.svh'), recursive=True)
    sv_files = glob.glob(os.path.join(directory, '**', '*.sv'), recursive=True)
    v_files = glob.glob(os.path.join(directory, '**', '*.v'), recursive=True)
    
    # Filter out files in the current directory to keep only relative paths
    all_files = sv_files + v_files + svh_files
    # Convert to relative paths from the directory
    relative_paths = [os.path.relpath(f, directory) for f in all_files]
    
    # Filter out files in metadata directory
    filtered_paths = [p for p in relative_paths if not p.startswith('metadata')]
    
    return sorted(filtered_paths)

def write_to_yaml(file_paths, output_file='config.yaml'):
    """
    Write file paths to yaml file
    """
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write("RTL_FILE:\n")
        for path in file_paths:
            f.write(f"  - {path}\n")
    
    print(f"Wrote {len(file_paths)} file paths to {output_file}")

def main():
    # Get all .sv and .v files in the current directory
    rtl_files = find_sv_v_files('.')
    
    # Write to yaml file
    write_to_yaml(rtl_files)

if __name__ == "__main__":
    main()