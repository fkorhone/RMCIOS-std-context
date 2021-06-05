/* 
RMCIOS - Reactive Multipurpose Control Input Output System
Copyright (c) 2018 Frans Korhonen

RMCIOS was originally developed at Institute for Atmospheric 
and Earth System Research / Physics, Faculty of Science, 
University of Helsinki, Finland

This file is part of RMCIOS. This notice was encoded using utf-8.

RMCIOS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RMCIOS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public Licenses
along with RMCIOS.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdio.h>
#include "RMCIOS-functions.h"

void mem_func (void *data, const struct context_rmcios *context, int id,
               enum function_rmcios function, enum type_rmcios paramtype,
               struct combo_rmcios *returnv, 
               int num_params,
               const union param_rmcios param);

void stdout_func (void *data, const struct context_rmcios *context, int id,
                  enum function_rmcios function, enum type_rmcios paramtype,
                  struct combo_rmcios *returnv, 
                  int num_params,
                  const union param_rmcios param);



///////////////////////////////////////////////////////////////////////////////////
// Channel for printf                                                            //
///////////////////////////////////////////////////////////////////////////////////
void stdout_func (void *data,
                        const struct context_rmcios *context, int id,
                        enum function_rmcios function,
                        enum type_rmcios paramtype,
                        struct combo_rmcios *returnv,
                        int num_params, const union param_rmcios param)
{
   switch (function)
   {
   case write_rmcios:
      if (num_params < 1)
         break;
      int blen = param_string_alloc_size (context, paramtype, param, 0);
      {
         char buffer[blen];
         const char *str;
         str = param_to_string (context, paramtype, param, 0, blen, buffer);
         puts (str);
      }
      break;
   }
}

// Channel function for allocating and freeing memory
void mem_func (void *data,
               const struct context_rmcios *context, int id,
               enum function_rmcios function,
               enum type_rmcios paramtype,
               struct combo_rmcios *returnv,
               int num_params, const union param_rmcios param)

{
   switch (function)
   {
   case help_rmcios:
      // MEMORY INTERFACE: 
      return_string (context, returnv,
                     " read mem \r\n -read ammount of free memory\r\n"
                     " write mem \r\n -read memory allocation block size\r\n"
                     " write mem n_bytes \r\n Allocate n bytes of memory\r\n"
                     "   -Returns address of the allocated memory\r\n"
                     "   -On n_bytes < 0 allocates complete allocation blocks\r\n"
                     "   -returns 0 length on failure\r\n"
                     " write mem (empty) addr(buffer/id)  \r\n"
                     "  -free memory pointed by addr in buffer\r\n"
                     );
      break;
   case read_rmcios:
      if (num_params == 0)      // read ammount of free memory
         if (num_params > 0)    //read memory block by remote access id
            if (num_params > 1) // +size bytes to read
               if (num_params > 2)      // +offset to start reading from\r\n");
                  break;

   case write_rmcios:
      if (num_params == 0)
      {
      } // Read memory allocation block size
      if (num_params == 1)      // Allocate n bytes of memory
      {
         int size = param_to_integer (context, paramtype,
                                      (const union param_rmcios)
                                      param, 0);
         void *ptr = malloc (size);
         return_binary (context, returnv, (char *) &ptr,
                        sizeof (ptr));
      }
      if (num_params > 1)
      {
      } // Write data to memory by access id
      if (num_params > 2)
      {
      } // +max size in bytes
      if (num_params > 3)
      {
      } // +starting at offset
      if (num_params == 2)      // Free 
      {
         if (param_to_integer
             (context, paramtype, (const union param_rmcios) param, 0) == 0)
         {
            char *ptr = NULL;
            param_to_binary (context, paramtype, param, 1,
                             sizeof (ptr), (char *) &ptr);
            if (ptr != NULL)
               free (ptr);
         }
      }
      break;
   }
}

void setup_std_context(struct context_rmcios *context) {
    int mem_channel =  create_channel (context, 0, 0, (class_rmcios)mem_func, 0);
    int stdout_channel = create_channel (context, 0, 0, (class_rmcios)stdout_func, 0);

    context->report = stdout_channel;
    context->warning = stdout_channel;
    context->errors = stdout_channel;
    context->mem = mem_channel;

    context->quemem = mem_channel;
}

