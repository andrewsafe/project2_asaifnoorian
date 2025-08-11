# CITATIONS

This document lists all external tools, libraries, and AI assistance used while building **Project2 - Andrew Saifnoorian**. No third‑party game “solutions” or source files were copied; only public APIs and documentation were referenced. All submitted source files were written by the author and reviewed/modified as needed.

---

## Open‑Source Libraries & Tools

- **Qt 6 (Qt Widgets)** — _LGPLv3_  
  Used for the GUI (`QMainWindow`, `QLabel`, `QPushButton`, `QButtonGroup`, `QSpinBox`, layouts). The project links against Qt and uses its public APIs only. No Qt source code was copied into the submission.  
  Typical kit used during development: _Qt 6.x, msvc2022_64_. Runtime deployment used `windeployqt`.

- **CMake** — _BSD 3‑Clause_  
  Used to configure and build the project (generate Visual Studio/Ninja builds). No CMake source was included in the submission.

- **Microsoft Visual C++ (MSVC) Toolchain** — _Microsoft EULA_  
  Used as the compiler/linker for Windows builds. Not distributed with the submission.

- **PlantUML** — _GPLv3_ (tool)  
  Used to render the class diagram from `class-diagram.puml`. Only the text diagram is included in the submission.

_(Optional, not part of the code submission)_

- **Xbox Game Bar** (Windows) — screen recording utility used to capture the demo video.

---

## AI Assistance

- **ChatGPT (GPT-5 Thinking) by OpenAI**  
  Assistance was used to:
  - Outline the object‑oriented design.
  - Scaffold core classes: `Card`, `Deck`, `Hand`, `Player`, `HandEvaluator`, and `EvalResult`.
  - Refine the Qt GUI (`MainWindow`) and event flow (Deal → Hold/Draw → Evaluate).
  - Debug build configuration on Windows (CMake, MSVC, Qt deployment) and fix minor Qt signal/slot mismatches.

All AI‑generated content was reviewed and adapted by the author; no external copyrighted code was pasted verbatim.

---

## Originality & Scope Notes

- No third‑party graphic assets were used; card faces rendered as text/symbols in the GUI.
- The project implements a single‑hand **(five‑card draw)** game with proper payouts and bankroll rules as specified.

---

## Citation

> Uses Qt 6 (LGPLv3), CMake (BSD 3‑Clause), MSVC toolchain, and PlantUML (GPLv3).  
> Assisted by ChatGPT (GPT-5 Thinking) for design, code scaffolding, and documentation.  
> All source code in the submission authored and reviewed by the student; no third‑party game code copied.
