<p align="center">
	<h1 align="center">lballoons</h2>
	<p align="center">A terminal "screensaver" written in C</p>
</p>
<p align="center">
	<a href="./LICENSE">
		<img alt="License" src="https://img.shields.io/badge/license-GPL-blue?color=7aca00"/>
	</a>
	<a href="https://github.com/LordOfTrident/lballoons/issues">
		<img alt="Issues" src="https://img.shields.io/github/issues/LordOfTrident/lballoons?color=0088ff"/>
	</a>
	<a href="https://github.com/LordOfTrident/lballoons/pulls">
		<img alt="GitHub pull requests" src="https://img.shields.io/github/issues-pr/LordOfTrident/lballoons?color=0088ff"/>
	</a>
	<br><br><br>
	<img width="500px" src="assets/img.png"/>
</p>

I made this purely to practice C since i have written almost no programs in it.
Inspired by [cmatrix](https://github.com/abishekvashok/cmatrix).

## Controls
| Key           | Description      |
|---------------|------------------|
| CTRL+Q/CTRL+C | Quit the program |

## Dependencies
- ncurses

## Make
Use `make all` to see all the make targets.

### Compiling
Run `make` or `make compile` which will create a binary in the `bin/` folder.

> If you want to change the compiler make uses, set the `C` variable. Example: `make C=gcc`
