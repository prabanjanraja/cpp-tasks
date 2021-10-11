// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef DYNAMICLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

extern "C" MATHLIBRARY_API double add(double a, double b);

extern "C" MATHLIBRARY_API double subtract(double a, double b);

extern "C" MATHLIBRARY_API double multiply(double a, double b);

extern "C" MATHLIBRARY_API double divide(double a, double b);