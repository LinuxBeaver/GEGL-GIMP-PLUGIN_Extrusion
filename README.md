# GEGL-extrusion-effect
GEGL does an extrusion effect on stylish text. This is mostly like the existing long shadow filter but it uses pixel data instead of a color fill.
Put extrusion .so/dll and bevel .so/dll in /gegl-0.4/plug-ins. It is okay to have multiple copies of GEGL:Bevel (The bonus filter that it comes with)
![image preview](extrusion_best.png )
 
 Make sure to use the behind blend mode or a layer behind the original. I did this intentionally so GEGL-extrusion could be more non-destructive and edited afterward manually.
 
 

## OS specific location to put GEGL Filter binaries 

Windows
 C:\\Users\<YOUR NAME>\AppData\Local\gegl-0.4\plug-ins
 
 Linux 
 /home/(USERNAME)/.local/share/gegl-0.4/plug-ins
 
 Linux (Flatpak)
 /home/(USERNAME)/.var/app/org.gimp.GIMP/data/gegl-0.4/plug-ins

