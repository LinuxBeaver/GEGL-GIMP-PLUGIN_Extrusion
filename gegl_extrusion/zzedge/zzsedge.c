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
 * Beaver 2022 zzhiddenoperations
 */

#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES

enum_start (gegl_edge_algo2)
   enum_value (GEGL_EDGE_GRADIENT2, "gradient2", N_("Gradient2"))
enum_end (GeglEdgeAlgo2)

property_enum (algorithm, _("Algorithm"),
               GeglEdgeAlgo2, gegl_edge_algo2,
               GEGL_EDGE_GRADIENT2)
  description (_("Edge detection algorithm"))


property_double (amount, _("Amount"), 2.0)
    description (_("Edge detection amount"))
    value_range (1.0, 10.0)
    ui_range    (1.0, 10.0)

property_enum (border_behavior, _("Border behavior"),
               GeglAbyssPolicy, gegl_abyss_policy,
               GEGL_ABYSS_CLAMP)
  description (_("Edge detection behavior"))


#else

#define GEGL_OP_META
#define GEGL_OP_NAME     zzsedge
#define GEGL_OP_C_SOURCE zzsedge.c

#include "gegl-op.h"

static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglNode *input, *output, *screen, *blur2;

  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");

  screen = gegl_node_new_child (gegl,
                                  "operation", "gegl:screen",
                                  NULL);

  blur2    = gegl_node_new_child (gegl,
                                  "operation", "gegl:edge",
                                  NULL);

  gegl_node_link_many (input, screen, output, NULL);
  gegl_node_link (input, blur2);
  gegl_node_connect_from (screen, "aux", blur2, "output");

  gegl_node_connect_from (screen, "aux", blur2, "output");




  gegl_operation_meta_redirect (operation, "algorithm", blur2, "algorithm");

  gegl_operation_meta_redirect (operation, "amount", blur2, "amount");

  gegl_operation_meta_redirect (operation, "border-behavior", blur2, "border-behavior");


}

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class;

  operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;

  gegl_operation_class_set_keys (operation_class,
    "name",        "gegl:zzescreen",
    "title",       _("zzescreen"),
    "categories",  "hidden",
    "reference-hash", "4511a9036gsa38a5125700fb4001b2ac",
    "description", _("Hidden operation to power Beaver's filters' "
                     ""),
    NULL);
}

#endif
