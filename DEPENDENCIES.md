# Dependencies

## Build environment

`Button.dsp`, `Proba.dsp`, and `bmp3/bmp3.dsp` are **Visual C++ 6.0**
project files using **MFC** (Microsoft Foundation Classes). Building
them requires Visual C++ 6.0 (or a compatible/migrated toolchain) with
MFC support; there is no modern (`.sln`/`.vcxproj`) project file.

`PLIME/` is a separate, third-party C/C++ codebase with its own
`makefile`; see LICENSE for its origin. It bundles its own X11 and
Tcl/Tk headers and a `tcl80.lib` library.

## Which loose root files belong to which project

`Button.dsp` and `Proba.dsp` were both created in this same directory
and share the root-level `ReadMe.txt`, `Resource.h`, `StdAfx.cpp`, and
`StdAfx.h` (confirmed from each `.dsp` file's own source list) --
they are not duplicated per project. Everything else at the
repository root (`ARDlg.*`, `Button.*`, `ButtonDoc.*`, `ButtonView.*`,
`CDetectDlg.*`, `CommonDlg.*`, `LDetectDlg.*`, `MainFrm.*`) belongs to
`Button`; `Proba.*` belongs to `Proba`.

## IDE-generated files

`Button.aps`, `Button.ncb`, `Button.opt`, `Button.plg`, `Button.suo`,
`Proba.aps`, `Proba.ncb`, `Proba.opt`, `Proba.plg`, and the equivalents
in `bmp3/` are Visual C++ 6.0 IDE-generated cache/session files (browse
database, workspace options, user options, build log). They are not
source code and are not needed to build the projects.

## Hardcoded paths

`ButtonDoc.cpp` contains hardcoded absolute paths to the original
author's machine (pointing to a `PLIME` working directory and
executable). Active instances are flagged with a `// EDIT:` comment
directly above them -- update these before running.
