# Jumper

  231250088 Liyan Ou 2/9/2024

  *Jumper* is a casual game written in C language that imitates the WeChat mini-program of the same name. Its design is very similar to the foreign game *Bottle Flip*. This project uses 2D planes for visual design, coupled with authentic sound effects, aiming to achieve the best gaming experience while gaining a deeper understanding of the functionalities of C and the game development process. It is also completed as a course project.

## Operating System

- Windows 11

## Environment

- mingw: gcc-13.2.0-llvm-16.0.6-mingw-w64ucrt-11.0.1-r2

## Third-party Libraries

- SDL2-2.26.0

## Installation

Enter the project source file directory: 

```sh
cd src/
```

Compile the project (Use gcc as example):

```sh
gcc -o Project main.c game.c utils/display.c utils/audio.c utils/input.c -Iinclude -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
```

Run the project and enjoy it: 

```sh
./Project
```

Or you can build it by **cmake**: 

```sh
mkdir build && cd build
cmake ..
make
./Project
```

## How to Play

- Game controls: 
  - ♟️ Press **Enter** to start the game.
  - 😊 Hold down the **Spacebar** to charge power, release it to jump, press **Enter** to use a **power-up** for a perfect jump.
  - 😨 Watch the power meter in the top left corner to determine the distance of your jump.
  - 💀 After dying, press **Enter** to restart the game.
- Jumping Platforms: 
  - Platforms in the game come in three colors: **blue**🔵 for regular platforms, **red**🔴 for **bonus score** platforms, and **green**🟢 for **power-up** platforms. Staying on a **special platform** for 3 seconds triggers a reward sound effect🎶 and grants the corresponding reward😋.

[Chinese Version]

- 游戏按键: 
  - ♟️敲击**回车键**即可开始游戏.
  - 😊游戏中**长按空格键**进行蓄力, **松开空格键**进行跳跃, 敲击**回车键**使用**道具**, 即触发一次完美跳跃.
  - 😨可观察左上角蓄力条决定跳跃远近.
  - 💀死亡后可敲击**回车键**重新开始游戏.
- 跳跃平台: 
  - 游戏中平台分为三种颜色, **蓝色**🔵为普通平台, **红色**🔴为**额外分数**平台, **绿色**🟢为**道具**平台, 在**特殊平台**上停留3秒即可触发奖励音效🎶并获得相应奖励😋.

## Insight

[Chinese Version]

  感谢助教giegie的提供SDL教程以及项目框架和思路, 让我少走了很多弯路, 但是还是存在着很多困难. 完成项目的过程就像是一个不断发现问题再解决问题的过程, 把想法变成现实并非易事, 其中存在着许多细节需要考量, 也有bug不断涌现和被修复, 最后由于DDL也导致很多想法也没有实现😭, 感动的是游戏还是能跑起来的😭. 收获颇丰, ~~主要是可以和别人吹水~~, 期待下一个项目.

  个人感觉 *灵机一动* 的地方是在于界面的转换这一个小结构, 我给开始, 游戏, 死亡分别设了0, 1, 2三个状态, 然后用while循环 (条件为非0) 在死亡和游戏界面中实现转换, 实现了游戏的重开效果 (如果为0就直接退出). ~~主要是我在洗澡的时候突然想到的, 当时非常的激动(雾).~~

  要求不高,  能跑就行😇.