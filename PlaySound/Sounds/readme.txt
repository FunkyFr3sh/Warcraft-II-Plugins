
## PlaySound Plugin ##

This plugin will play a sound of your choice on certain events. e.g. the host just started the game or someone joined your game. It's useful in case your game is minimized and you don't want to miss the game start or you want to hear when someone joined your game.

You can replace the .wav files with any sounds you want, I got the ones that are included from here: https://www.soundjay.com/

If you only want to get notified about a game start but you don't want to get notified about someone joining a game then just delete the matching .wav files.



## Supported Filenames ##

JoinGame.wav        - Plays when a player joined a game

StartGame.wav       - Plays when the host started the game

LeaveGame.wav       - Plays when a player left a game

Message.wav         - Plays when a player sent a message

PrivateMessage.wav  - Plays when you received a private message

GameEnd.wav         - Plays when the score screen appears

Kicked.wav          - Plays when you get banned or the host left the game



## Example ##

Use "JoinGame.wav" if you want the sound to play no matter if the game window got the focus or not.

Use "JoinGameNoFocus.wav" if you only want the sound to play if the game doesn't have the focus / is minimized (Make sure you don't have "JoinGame.wav" in the folder)

Use "JoinGameFocus.wav" if you only want the sound to play if the game is active and got the focus (Make sure you don't have "JoinGame.wav" in the folder)

