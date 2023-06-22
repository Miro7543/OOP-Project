#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H

#include "Files.h"

const set<string> supportedShapes={
    "rectangle",
    "circle",
    "ellipse",
    "line",
    "polyline",
    "polygon"
};

const map<string, function<void(File &)>> commandEntries = {
    {"open", [](File &f)
     { f.open(); }},

    {"close", [](File &f)
     { f.close(); }},

    {"save", [](File &f)
     { f.save(); }},

    {"saveas", [](File &f)
     { f.saveAs(); }},

    {"help", [](File &f)
     { f.help(); }},

    {"print", [](File &f)
     { f.print(); }},

    {"create", [](File &f)
     {  f.create(); }},

    {"translate", [](File &f)
     {  f.translate(); }},
    
    {"erase", [](File &f)
     {  f.erase(); }},
    
    {"within", [](File &f)
     {  f.within(); }},
    
    {"area", [](File &f)
     {  f.area(); }},
    
    {"perimeter", [](File &f)
     {  f.perimeter(); }},
    
    {"length", [](File &f)
     {  f.length(); }},};

const map<string, function<BasicShape *(int)>> Factory = {
    {"g>", [](int d) -> BasicShape *
     { return new Group(d); }},
    
    {"g", [](int d) -> BasicShape *
     { return new Group(d); }},

    {"circle", [](int d) -> BasicShape *
     { return new Circle(); }},
    
    {"rect", [](int d) -> BasicShape *
     { return new Rect(); }},
    
    {"rectangle", [](int d) -> BasicShape *
     { return new Rect(); }},
    
    {"ellipse", [](int d) -> BasicShape *
     { return new Ellipse(); }},
    
    {"line", [](int d) -> BasicShape *
     { return new Line(); }},
    
    {"polyline", [](int d) -> BasicShape *
     { return new PolyLine(); }},
    
    {"polygon", [](int d) -> BasicShape *
     { return new Polygon(); }}
};



#endif