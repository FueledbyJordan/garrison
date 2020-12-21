# What is Garrison?
Garrison is an open-sourced project that is aimed at making Linux config deployment less painful.

## Building

### Source
### Docker

#### Testing

## Install

## Usage
```garrison [options]```

Options:

```
-i directory --input directory    The directory where garrison looks for files.  If this option is not specified, garrison assumes you want the current directory.

-o directory --output directory   This is where garrison places your symlinks. If this option is not specified, garrison assumes you want the directory above the current directory.

-c file --config file    The config file to use.  Garrison will read the configuration file and then will apply any given input parameters.  The default configuration file name is garrison.cfg.

-f --force    Force the operation. Note that this will overwrite existing links and files.

-I "REGEX" --Include "REGEX"    Include the files and directories that match the provided regex pattern. This can be called multiple times.

-E "REGEX" --Exclude "REGEX"    Exclude the files and directories that match the provided regex pattern. This can be called multiple times.

-C "REGEX" --Copy "REGEX"    Copy the files and directories that match the provided regex pattern. This can be called multiple times.

-g  --generate    Generate a sample config file.  Redirect the output of this to your config file.

-d  --dry-run    Don't do anything. Just print out what would happen.

-v --version    Show garrison version.

-h --help    Show garrison help.
```

### Configuration file
The default configuration file is garrison.cfg.  Garrison assumes that the configuration file is in the current directory.
An example configuration file:

```
# Some comment in your garrison.cfg
Input = .
Output = /home/garrison\_user
Include = "^\.vim\/" "^\.bashrc" "^\.files"
Include += "^\.bash_aliases"
Copy = "^\.directory\_to\_copy\\/"
Exclude = "^\.files\/some_secret_file" "^\.files\/some_other_secret_file"
Exclude += "^\.vim\/some_secret_file"
Exclude += "^\.directory_to_copy\/some_file_to_leave_out"
```

## Alternative Programs
* [stow](https://www.gnu.org/software/stow)
