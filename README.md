# JNI-Dex-Sideload
Credits: Kp7742 (Original Java Github Source)

What: Using any active activity context, you can load and initialize dex files that are not present in the apk. 

Pros:

▪︎ Harder to reverse by third parties as dex will not be present in apk.

▪︎ Can download dex files OTA (Over the Air) to perform changes to the game without updating the application itself.

Cons:

▪︎ Some emulators will not support this.

▪︎ If file is compromised, 3rd party users can make changes to the application without voiding application integrity. 
