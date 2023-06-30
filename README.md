# GEGL-extrusion-effect
GEGL does an extrusion effect on stylish text. 

This plugin ships with two bonus plugins that are useful on their own. Bevel and Edge Smoother. If you compile you must compile both them of them. If you use binaries just grab them. If you already have bevel consider recompiling or over riding the binary to get the latest version from mid 2023. 

![image preview](extrusion_best.png )
 
 Make sure to use the behind blend mode or a layer behind the original. I did this intentionally so GEGL-extrusion could be more non-destructive and edited afterward manually.
 
 

## OS specific location to put GEGL Filter binaries 

Windows
 C:\\Users\<YOUR NAME>\AppData\Local\gegl-0.4\plug-ins
 
 Linux 
 /home/(USERNAME)/.local/share/gegl-0.4/plug-ins
 
 Linux (Flatpak)
 /home/(USERNAME)/.var/app/org.gimp.GIMP/data/gegl-0.4/plug-ins

