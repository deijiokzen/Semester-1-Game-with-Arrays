# Semester 1- Game with Arrays

For the Version of the game with Audio, refer to this [link](https://mega.nz/file/FKJSAQIJ#7xEBSFhhd5SBRDVH4sfFwmSTI6tdW-wL2AuOnQjVyg0)
![](RackMultipart20211127-4-kmtobv_html_e1b366a266673dda.png)

**PROGRAMMING FUNDAMENTALS PROJECT REPORT**

| **Project Title:** | Bridges and Castle: Text Based Adventure/Puzzle Game |
| --- | --- |

| **Group Members** | **Roll no.** | **Names** |
| --- | --- | --- |
|
**1**
 |
**K190229** | **Saud Ahmed Abbasi** |
| --- | --- | --- |
|
**2**
 | **K190181**
 | **Umer Ahmed**
 |
| **3** | **K191512** | **Zaid Bin Shahab** |
| --- | --- | --- |

# SECTION: B

| **Tools used:** | **C-Language, Windows (Operating System)** |
| --- | --- |

**Course Teacher: Basit Jasani**

**Programming Fundamentals**

# **FAST-National University of Computer &amp; Emerging Sciences, Karachi.**

**Introduction**

A text-based adventure/puzzle game that challenges the player with puzzles and mini-games, containing visuals, sounds, and a basic story.

**Salient Features**

- ASCII visuals printed through the use of Filing.
- &quot;Bridges&quot; puzzle game through use of recursive functions.
- Puzzle game board displayed through 2-Dimentional Arrays.
- Tick Tack Toe mini-game with 3 levels of difficulty using loops and if-statements.
- Hangman mini-game with character array/string.
- Points system to determine Game Over/Ending.
- Structure to display previous scores.

**Problem Statement:**

The player inputs the movements in puzzles (Bridges/Hallways) and the program has to follow those inputs to display the player on-screen.

Hangman and Tick Tack Toe mini-games also take the users input in the form of characters and numbers respectively, which have to be displayed on the screen, following the rules of the respective games.

The program has to display different visuals according to the player&#39;s situation (winning/losing etc.).

**Solution:**

The play area is displayed through 2-Dimentional array, so the player&#39;s position is also saved in that array in the Bridges/Hallways Puzzle. The movement is done through functions which receive &#39;w&#39;, &#39;a&#39;, &#39;s&#39;, &#39;d&#39; characters as input, and changes the player&#39;s position in the 2D Array, which is then displayed on-screen.

Hangman receives input as a character and then the function compares the character with the hardcoded character array.

Tick Tack Toe has a board displayed through a simple array of nine elements, each of which corresponds to a position on the board. In response to the players input the program checks through if-else statements in loops, to see the best possible move according to the given level.

This is done through functions which read files through file pointers and print the characters in the file when the point threshold is low/high enough.
