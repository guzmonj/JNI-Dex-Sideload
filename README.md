# JNI-Dex-Sideload
Credits: Kp7742 (Original Java Github Source)

What: Using any active activity context, you can load and initialize DEX files that are not present in the APK. 

Pros:

▪︎ Harder to reverse by third parties as DEX will not be present in APK.

▪︎ Can download DEX files OTA (over the air) to perform changes without actually updating the application itself.

Cons:

▪︎ Some emulators will not support this.

▪︎ If file is compromised, 3rd party users can make changes to the application without voiding application integrity. 
