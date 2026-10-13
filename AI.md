# AI Assistant Guide — Nightfall

This file gives AI assistants (LLMs) the context and rules for working on this repository.

## Rules of engagement

- **Do not write code for this project by default.** Every line in this repository is
  written by hand by the author. This is a deliberate, educational choice and part of
  a possible bachelor thesis.
- **Default behavior:** explain the problem and show a minimal snippet of how to fix it.
  Never edit files in the repository unless the author explicitly asks for it
  (e.g. "edit the file", "write it into the file").
- **Before editing any file, ask for confirmation**, even when the author has asked for
  a change. Something that doesn't explicitly mean "edit the files" is a request
  for an explanation and a snippet, not for an edit.
- **Files written or substantially changed by an AI** must start with a comment marking
  them as AI-generated (model and the request), so it stays clear which parts are
  not hand-written.
- **Allowed and encouraged:**
  - Research: explaining concepts, algorithms, APIs, trade-offs and how other engines solve a problem.
  - Debugging: reading code, finding the cause of bugs and crashes, explaining compiler, linker and runtime errors.
  - Review: pointing out bugs, performance problems, undefined behavior and design issues.
  - Pointing to documentation, papers, talks and reference implementations.
- **When illustrating a concept**, keep snippets minimal and generic: pseudo-code or small
  isolated examples, not drop-in implementations for this codebase.

## Project overview

Nightfall is a game engine with a native editor, built as much as possible from scratch. Third-party libraries are used only where writing them would not be an efficient use of time (UI, docking, asset loading, etc.).

### Nightfall Engine
- **Language:** C++23
- **Principles:**
  - **Performance:** core systems and hot paths use data-oriented, cache-friendly design.
  - **High modularity:** a minimal core, with optional modules chosen per application ("use only what is needed").
  - **C# gameplay code:** planned, not yet designed.
  - **Cross-platform:** intended long term, including consoles.
- **Current target:** Windows 11 only. Development and testing focus solely on Windows for now.

### Nightfall Editor
- **Language / UI:** C# with WPF (Windows only).
- **Separate process:** the editor runs independently of the engine so engine crashes do not take down the editor or lose work.
- **Communication:** editor and engine communicate in both directions over TCP/IP.

### Nightfall Tools
- Not yet defined. A custom build system (Nightfall Build System) is under consideration.

## Third-party libraries

| Component | Library | Purpose |
|---|---|---|
| Engine | [Dear ImGui](https://github.com/ocornut/imgui) | Immediate-mode GUI for C++ |
| Editor | [AvalonDock](https://github.com/Dirkster99/AvalonDock) | Docking layout for WPF |

Asset loading libraries are planned but not yet chosen.

## Guidance for answers

- Prefer data-oriented, cache-aware solutions for engine-side questions, and explain the performance reasoning.
- For editor questions, assume C#/WPF and keep the engine–editor process boundary in mind: the editor must survive engine crashes.
- When suggesting a third-party library, justify why writing it from scratch is not worth it, in line with the project's philosophy.
