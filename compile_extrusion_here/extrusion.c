/* This file is an image processing operation for GEGL
 *
 * GEGL is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * GEGL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GEGL; if not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright 2006 Øyvind Kolås <pippin@gimp.org>
 * 2022 Beaver (GEGL extrusion) Credit also goes to Mahvin, a moderator of GimpChat.com for making Beaver's GEGL Graph discovery better
 */

#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES

property_double (center_x, _("Center X"), -2.1)
    value_range (-3.5, 3.5)
    ui_range    (-3.5, 3.5)
    ui_meta     ("unit", "relative-coordinate")
    ui_meta     ("axis", "x")

property_double (center_y, _("Center Y"), -1.4)
    value_range (-3.5, 3.5)
    ui_range    (-3.5, 3.5)
    ui_meta     ("unit", "relative-coordinate")
    ui_meta     ("axis", "y")

property_double (factor, _("Length of extrusion"), 0.005)
    value_range (0, 0.180)
    ui_range    (0, 0.180)
    ui_gamma    (2.0)


enum_start (gegl_edge_algo1)
   enum_value (GEGL_EDGE_GRADIENT1, "gradient1", N_("Gradient1"))
enum_end (GeglEdgeAlgo1)

property_enum (algorithm, _("Algorithm"),
               GeglEdgeAlgo1, gegl_edge_algo1,
               GEGL_EDGE_GRADIENT1)
  description (_("Edge detection algorithm"))
    ui_meta     ("role", "output-extent")



property_double (opacity, _("Slide up to enable colors on extrusion"), 0.0)
    description (_("Global opacity value that is always used on top of the optional auxiliary input buffer."))
    value_range (0, 1)
    ui_range    (0.0, 1)

property_double (amount, _("Amount of colors on the extrusion"), 3.7)
    description (_("Edge detection amount"))
    value_range (1.0, 10.0)
    ui_range    (1.0, 10.0)


property_int (depth, _("Increase roughness"), 14)
    description (_("Filter width"))
    value_range (1, 30)

property_double (value, _("Short trails work eitheway. Long trails need lower."), 0.100)
    value_range (0.10, 0.43)
    ui_range    (0.10, 0.43)
    description(_("Scalar threshold level (overridden if an auxiliary input buffer is provided.)."))

property_int  (iterations, _("Noise Reduction to smear colors"), 0)
  description (_("Controls the number of iterations; lower values give less plastic results"))
  value_range (0, 25)
  ui_range    (0, 8)


property_double (black_level, _("Black level to remove hot pixels"), 0.0)
    description (_("Adjust the black level"))
  value_range (0, 1)
    value_range (0.0, 0.10)

property_double (exposure, _("Exposure decreasation to remove hot pixels"), -1.40)
    description (_("Relative brightness change in stops"))
  value_range (-5, 5)
    ui_range    (-5.0, 5.0)

property_int  (medianradius, _("Increase  median radius to remove hot pixels."), 1)
  value_range (0, 4)
  ui_range    (0, 4)
  ui_meta     ("unit", "pixel-distance")
  description (_("Neighborhood radius, a negative value will calculate with inverted percentiles"))

property_double  (percentile, _("Decrease median percentile to remove hot pixels."), 50)
  value_range (40, 50)
  description (_("Neighborhood color percentile"))




#else

#define GEGL_OP_META
#define GEGL_OP_NAME     extrusion
#define GEGL_OP_C_SOURCE extrusion.c

#include "gegl-op.h"

static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglNode *input, *output, *zmb, *edge, *screen, *multiply, *alpha, *nr, *nop2, *box, *nop, *bevel, *opacity, *median, *chroma, *brightness;

  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");


  nr = gegl_node_new_child (gegl,
                                  "operation", "gegl:noise-reduction",
                                  NULL);


  screen = gegl_node_new_child (gegl,
                                  "operation", "gegl:screen",
                                  NULL);


  edge = gegl_node_new_child (gegl,
                                  "operation", "gegl:edge",
                                  NULL);


  zmb = gegl_node_new_child (gegl,
                                  "operation", "gegl:motion-blur-zoom",
                                  NULL);

   multiply = gegl_node_new_child (gegl,
                                  "operation", "gegl:multiply",
                                  NULL);

   bevel = gegl_node_new_child (gegl,
                                  "operation", "lb:bevel",
                                  NULL);



   box = gegl_node_new_child (gegl,
                                  "operation", "gegl:box-blur",
                                  NULL);


   alpha = gegl_node_new_child (gegl,
                                  "operation", "gimp:threshold-alpha",
                                  NULL);

   brightness = gegl_node_new_child (gegl,
                                  "operation", "gegl:exposure",
                                  NULL);

  median = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur",
                                  NULL);

  chroma = gegl_node_new_child (gegl,
                                  "operation", "gegl:hue-chroma",
                                  NULL);

  nop = gegl_node_new_child (gegl,
                                  "operation", "gegl:nop",
                                  NULL);


  nop2 = gegl_node_new_child (gegl,
                                  "operation", "gegl:nop",
                                  NULL);


  opacity = gegl_node_new_child (gegl,
                                  "operation", "gegl:opacity",
                                  NULL);









  gegl_node_link_many (input, zmb, nop, multiply, alpha, nop2, screen, median, nr, chroma, brightness, output, NULL);
  gegl_node_connect_from (multiply, "aux", bevel, "output"); 
  gegl_node_connect_from (screen, "aux", opacity, "output"); 
  gegl_node_link_many (nop, bevel, NULL);
  gegl_node_link_many (nop2, edge, opacity, NULL);



  gegl_operation_meta_redirect (operation, "algorithm", edge, "algorithm");

  gegl_operation_meta_redirect (operation, "border-behavior", edge, "border-behavior");

  gegl_operation_meta_redirect (operation, "amount", edge, "amount");

   gegl_operation_meta_redirect (operation, "exposure", brightness, "exposure");

   gegl_operation_meta_redirect (operation, "black_level", brightness, "black-level");

  gegl_operation_meta_redirect (operation, "factor", zmb, "factor");

  gegl_operation_meta_redirect (operation, "center_x", zmb, "center-x");

  gegl_operation_meta_redirect (operation, "center_y", zmb, "center-y");

  gegl_operation_meta_redirect (operation, "iterations", nr, "iterations");

  gegl_operation_meta_redirect (operation, "box", box, "box");                                                      

  gegl_operation_meta_redirect (operation, "value", alpha, "value");



  gegl_operation_meta_redirect (operation, "depth", bevel, "bevel2");

  gegl_operation_meta_redirect (operation, "medianradius", median, "radius");
  gegl_operation_meta_redirect (operation, "percentile", median, "percentile");
  gegl_operation_meta_redirect (operation, "chroma", chroma, "chroma");
  gegl_operation_meta_redirect (operation, "opacity", opacity, "value");





}

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class;

  operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;

  gegl_operation_class_set_keys (operation_class,
    "name",        "lb:extrusion",
    "title",       _("Extrusion for styled text"),
    "categories",  "Aristic",
    "reference-hash", "156j6bfzaa5014f2ks3b27ac",
    "description", _("GEGL will stretch the pixels of stylish text and make an extrusion effect. It is mandatory that you set the blending option mode to behind or put this on a layer below the original image."
                     ""),
    NULL);
}

#endif
