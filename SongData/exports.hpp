#ifndef SONGDATA_EXPORTS_HPP_INCLUDED
#define SONGDATA_EXPORTS_HPP_INCLUDED
#pragma once

#ifdef SONGDATA_EXPORTS
#define SONGDATA_API(return_type) extern "C" __declspec(dllexport) return_type
#else
#define SONGDATA_API(return_type) extern "C" __declspec(dllimport) return_type
#endif

#endif // SONGDATA_EXPORTS_HPP_INCLUDED
