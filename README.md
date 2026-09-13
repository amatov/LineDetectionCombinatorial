## LineDetectionCombinatorial

## Quick start

This repository contains the Visual C++ 6.0 MFC GUI (`Button`) for a
fast line-detection computer vision algorithm, plus two related
projects (`Proba`, `bmp3`). See [DEPENDENCIES.md](DEPENDENCIES.md) for
the Visual C++ 6.0 / MFC build requirement.

## Repository contents

- `Button.*`, `ARDlg.*`, `ButtonDoc.*`, `ButtonView.*`, `CDetectDlg.*`,
  `CommonDlg.*`, `LDetectDlg.*`, `MainFrm.*` -- the `Button` GUI
  project.
- `Proba.*` -- a separate DLL project, sharing this directory's
  `ReadMe.txt`/`Resource.h`/`StdAfx.*` with `Button` (see
  DEPENDENCIES.md).
- `bmp3/` -- a separate, self-contained console project that displays
  a BMP image via SDL.
- [`media/MatovGUI2001.png`](media/MatovGUI2001.png) -- a screenshot of the computer vision GUI
  demonstrating detection of primitive shapes (lines, circles, and
  ellipses) in an image.
- `reports/` -- a conference poster PDF.
- **License:** see [LICENSE](LICENSE) -- research/educational use, with
  separate terms noted for the bundled third-party `PLIME/` folder.

## About

C++ code I wrote for a graphical user interface of a fast line detection computer vision algorithm (see the PLIME folder) developed in the lab of Daniel Mlynek, PhD (Integrated Systems Laboratory) at the EPFL during my work on the efficient detection and tracking of primitive shapes (lines, circles and ellipses), which is of great interest to the computer vision community - in particular, in the context of the analysis of multiple circles and ellipses.

Marco Mattavelli, Vince Noel, Edo Amaldi "Fast Line Detection Algorithms Based on Combinatorial Optimization" (2001) https://researchgate.net/publication/220701250_Fast_Line_Detection_Algorithms_Based_on_Combinatorial_Optimization

