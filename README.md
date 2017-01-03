# copy-imgs

This is a simple tool for myself to copy images

# usage

    Usage: CopyImgs.exe -v <version> [options] <top-src-dir> <dst-dir>
    Copy all the images you built under <top-src-dir> to <dst-dir>

      -v <version>:  Major version and minor version, must be 4 digit.
                     This option is Mandatory.
      -m <model>:    Model name, 0001 by default
      -p <proj>:     Project name, PLT by default
      -r:            Do not rename images, will rename images by default.

    <top-src-dir> is the root directory of your source code, <dst-dir> is
    the direcory where you want copy images to. If the <dst-dir> do not
    exist, it will be created. These two arguments are Mandatory.

    ex: CopyImgs.exe -v 2222 -m 00WW \\IP\path\to\source PLT
