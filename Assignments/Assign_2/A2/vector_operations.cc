#include "base/logging.hh"
#include "base/trace.hh"
#include "/home/monsoon2023/aviral21029/gem5/src/learning_gem5/A2/vector_operations.hh"
#include <iostream>
#include <cmath>
#include "debug/VectorSubtraction.hh"
#include "debug/VectorCrossProduct.hh"
#include "debug/VectorNormalization.hh"
#include "debug/PrintVector.hh"

namespace gem5
{
    int v1[3] = {1, 2, 3};
    int v2[3] = {4, 5, 6};

VectorOperations::VectorOperations(const VectorOperationsParams &params) : 
    SimObject(params), 
    task1([this]{vectorCrossProduct();}, name()),
    task2([this]{normalizeVector();}, name()),
    task3([this]{vectorSubtraction();}, name()), 
    latency(params.waitingTIME)
{
    DPRINTF(PrintVector, "Input vector 1: [ %d %d %d ] \n", v1[0], v1[1], v1[2]);
    DPRINTF(PrintVector, "Input vector 2: [ %d %d %d ] \n", v2[0], v2[1], v2[2]);
}

void VectorOperations::startup()
{
    schedule(task1, latency);
    schedule(task2, latency);
    schedule(task3, latency);
}

void VectorOperations::vectorCrossProduct()
{
    int result[3];

    result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    result[2] = v1[0] * v2[1] - v1[1] * v2[0];

    DPRINTF(VectorCrossProduct, "Vector Cross Product Result: [ %d, %d, %d ] \n", result[0], result[1], result[2]);
}

void VectorOperations::normalizeVector()
{
    int length1 = sqrt(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]);
    int length2 = sqrt(v2[0] * v2[0] + v2[1] * v2[1] + v2[2] * v2[2]);

    int normalized1[3];
    int normalized2[3];

    for (int i = 0; i < 3; ++i)
    {
        normalized1[i] = v1[i] / length1;
        normalized2[i] = v2[i] / length2;
    }

    DPRINTF(VectorNormalization, "Normalized Vector 1: [ %d, %d, %d ] \n", normalized1[0], normalized1[1], normalized1[2]);
    DPRINTF(VectorNormalization, "Normalized Vector 2: [ %d, %d, %d ] \n", normalized2[0], normalized2[1], normalized2[2]);
}

void VectorOperations::vectorSubtraction()
{
    int result[3];

    for (int i = 0; i < 3; ++i)
    {
        result[i] = v1[i] - v2[i];
    }

    DPRINTF(VectorSubtraction, "Vector Subtraction Result: [%d, %d, %d]\n", result[0], result[1], result[2]);
}

}
