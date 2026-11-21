# FH3-TrafficCars

<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/cfec9ecd-fef5-4811-885a-6a33f4f9a476" />


A port of [TrafficCars for FH2](https://github.com/suderek22/FH2_TrafficCars) to Forza Horizon 3 on Azimuth. It clears the traffic-car classification so those cars can be used like other cars where available, for example through car packs.

## Requirements and installation

- Forza Horizon 3 through Azimuth with the June 5, 2018 Xbox One executable.
- [FH3 ModPlatform 1.4.2 or later](https://github.com/Levilente/FH3_ModPlatform/releases/tag/v1.4.2).

Copy `fh3-mods/FH3-TrafficCars.dll` from the release ZIP into the `fh3-mods` folder next to `azimuth.exe` and start the game. Check `fh3-mods/platform.log` for the registration message and database errors.

The mod fills missing car buckets, clears the Autoshow exclusion flag for traffic cars, and removes their traffic classification. The PG Bus, PG Box Truck, and Ford Transit go under **Vans and Utility**, alongside the existing Ford Pursuit Ute traffic variant. Existing bucket assignments are preserved.

ModPlatform applies these changes to a copy of `media/Stripped/gamedbRC.slt` in `mediaoverride`. To uninstall, remove the DLL and restart the game so ModPlatform can rebuild the override using the remaining mods.

ModPlatform checks [FH3-TrafficCars releases](https://github.com/suderek22/FH3_TrafficCars/releases) for updates.
