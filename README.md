### Bruh Falls

- **Bro Falls: Ultimate Showdown Cheat**
    - Basically a free fall guys clone with no AC lmao, can be found on steam [here](https://store.steampowered.com/app/1590320/Bro_Falls_Ultimate_Showdown/).
    - This cheat is just a PoC and a part of a cheat speedrun i was doing with a friend, it was done under two hours in the vc with da boys in my server :).
<br>

- The project has all the game functions and classes implemented in `il2cpp-functions.h` and `il2cpp-types.h` so you can hook anything with ease.

<br>

- Dumped the assembles with [Il2CppDumper](https://github.com/Perfare/Il2CppDumper) and the dll project using [Il2CppInspector](https://github.com/djkaty/Il2CppInspector), however the inspector is not gonna work for you you have to fix it yourself by editing the source code, but i won't spoonfeed you how **since i don't encourage cheating**.

<br>

- Main runtime code is located at `user/main.cpp` which bascially hooks ragdoll rpc (so you don't get ragdoll deathes lol) and grap rpc so no one can grap you :okayge:. Also it creates a thread and waits for keys `+` or `-` to de/increase your speed and jump height by 100.

<br>

- The game has no AC so you can use whatever injector you like lmao, the game is also full of exploits and has no server sided checks on 90% of the stuff so, BE CREATIVE AND FEEL FREE TO PR THE REPO!.
