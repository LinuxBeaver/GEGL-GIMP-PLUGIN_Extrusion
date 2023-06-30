# GEGL-extrusion-effect
GEGL does an extrusion effect on pre-existing stylish text. 

![image](https://github.com/LinuxBeaver/GEGL-extrusion-effect/assets/78667207/3d6dc1ed-95aa-4bd5-9112-5764778e58f4)

![image](https://github.com/LinuxBeaver/GEGL-extrusion-effect/assets/78667207/d19ecb01-b3c9-425f-aa07-425e7521598b)


This plugin ships with two bonus plugins that are useful on their own. Bevel and Edge Smoother. If you compile you must compile both them of them. If you use binaries just grab them. If you already have bevel consider recompiling or over riding the binary to get the latest version from mid 2023. 

 
In earlier releases Extrusion requires the "behind" blend mode in Gimp. The final release (june 2023) doesn't have this issue. It can still extract a stand alone extrusion with a checkbox.
 

## OS specific location to put GEGL Filter binaries 

Windows
 C:\\Users\<YOUR NAME>\AppData\Local\gegl-0.4\plug-ins
 
 Linux 
 /home/(USERNAME)/.local/share/gegl-0.4/plug-ins
 
 Linux (Flatpak)
 /home/(USERNAME)/.var/app/org.gimp.GIMP/data/gegl-0.4/plug-ins

