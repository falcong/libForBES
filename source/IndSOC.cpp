/*
 * File:   IndSOC.cpp
 * Author: Lorenzo Stella
 *
 * Created on September 21, 2015, 11:08 AM
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

#include "IndSOC.h"

IndSOC::IndSOC(int n) : Function() {
    this->m_n = n;
}

IndSOC::~IndSOC() {
}

int IndSOC::call(Matrix& x, double& f) {
    if (!x.isColumnVector()) {
        throw std::invalid_argument("x must be a vector");
    }
    volatile bool isInside = true;
    volatile size_t i = 0;
    size_t n = x.getNrows();
    double squaredNorm = 0;
    double t = x[n - 1];

    while (i < n - 1 && isInside) {
        double xi;
        xi = x[i];
        squaredNorm += xi*xi;
        i++;
    }
    f = (t >= sqrt(squaredNorm)) ? 0.0 : INFINITY;
    return ForBESUtils::STATUS_OK;
}

int IndSOC::callProx(Matrix& x, double gamma, Matrix& prox) {
    double f_at_prox;
    return callProx(x, gamma, prox, f_at_prox);
}

int IndSOC::callProx(Matrix& x, double gamma, Matrix& prox, double& f_at_prox) {
    f_at_prox = 0.0;
    if (!x.isColumnVector()) {
        throw std::invalid_argument("x must be a vector");
    }
    size_t i = 0;
    size_t n = x.getNrows();
    double norm = 0, xi, scal;
    double t = x[n-1];

    while (i < n - 1) {
        xi = x[i];
        norm += xi*xi;
        i++;
    }

    norm = sqrt(norm);

    if (t > norm) {
        prox = Matrix(x); // prox = x
    } else if (t < -norm) { // prox = zero vector
        for (size_t j = 0; j < n; j++) {
            prox[j] = 0.0;
        }
    } else {
        /* perform actual projection here */
        scal = (1 + t / norm) / 2;
        for (size_t j = 0; j < n - 1; j++) {
            xi = x[j];
            prox[j] = scal * xi;
        }
        prox[n - 1] = (norm + t) / 2.0;
    }
    return ForBESUtils::STATUS_OK;
}

FunctionOntologicalClass IndSOC::category() {
    return FunctionOntologyRegistry::indicator();
}
