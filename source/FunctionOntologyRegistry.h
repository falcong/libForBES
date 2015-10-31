/* 
 * File:   FunctionOntologyRegistry.h
 * Author: chung
 *
 * Created on October 28, 2015, 8:16 PM
 * 
 * ForBES is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *  
 * ForBES is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with ForBES. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FUNCTIONONTOLOGYREGISTRY_H
#define	FUNCTIONONTOLOGYREGISTRY_H

#include "FunctionOntologicalClass.h"
#include "Function.h"
#include <iostream>

/**
 * 
 * \brief Registry of standard ontological classes.
 */
class FunctionOntologyRegistry {
public:

    static string nameSpace() {
        static string ns("fb");
        return ns;
    }

    static FunctionOntologicalClass function() {
        /*
         * NOTE:
         * The lifetime of function static variables begins the first time 
         * the program flow encounters the declaration and it ends at program 
         * termination.
         */
        static FunctionOntologicalClass generic_function("Function");
        return generic_function;
    }

    static FunctionOntologicalClass quadratic() {
        static bool defines_conjugate = true;
        static bool defines_conjugate_grad = true;
        static bool defines_f = true;
        static bool defines_grad = true;
        static bool defines_prox = false;
        static FunctionOntologicalClass quad(
                defines_conjugate,
                defines_conjugate_grad,
                defines_f,
                defines_grad,
                defines_prox,
                "Quadratic",
                function());
        return quad;
    }

    static FunctionOntologicalClass distance() {
        static bool defines_conjugate = false;
        static bool defines_conjugate_grad = false;
        static bool defines_f = true;
        static bool defines_grad = false;
        static bool defines_prox = false;
        static FunctionOntologicalClass dist(
                defines_conjugate,
                defines_conjugate_grad,
                defines_f,
                defines_grad,
                defines_prox,
                "Distance",
                function());
        return dist;
    }

    static FunctionOntologicalClass indicator() {
        static bool defines_conjugate = false;
        static bool defines_conjugate_grad = false;
        static bool defines_f = true;
        static bool defines_grad = false;
        static bool defines_prox = true;
        static FunctionOntologicalClass dist(
                defines_conjugate,
                defines_conjugate_grad,
                defines_f,
                defines_grad,
                defines_prox,
                "Indicator",
                function());
        return dist;
    }

    static FunctionOntologicalClass loss() {
        static bool defines_conjugate = false;
        static bool defines_conjugate_grad = false;
        static bool defines_f = true;
        static bool defines_grad = true;
        static bool defines_prox = false;
        static FunctionOntologicalClass loss(
                defines_conjugate,
                defines_conjugate_grad,
                defines_f,
                defines_grad,
                defines_prox,
                "LossFunction",
                function());
        return loss;
    }

    static FunctionOntologicalClass norm() {
        static bool defines_conjugate = true;
        static bool defines_conjugate_grad = false;
        static bool defines_f = true;
        static bool defines_grad = false;
        static bool defines_prox = true;
        static FunctionOntologicalClass norm(
                defines_conjugate,
                defines_conjugate_grad,
                defines_f,
                defines_grad,
                defines_prox,
                "Norm",
                function());
        return norm;
    }


private:
    FunctionOntologyRegistry();
    virtual ~FunctionOntologyRegistry();




};

#endif	/* FUNCTIONONTOLOGYREGISTRY_H */

