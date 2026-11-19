#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include <cmath>
#include "SVGDocumentBuilder.h"
#include "Rect.h"
#include "Circle.h"
#include "Line.h"
#include "Polyline.h"
#include "Path.h"
#include "Use.h"
#include "Group.h"
#include "Validator.h"

int readInt(const std::string& prompt, int minValue, int maxValue) {
    while (true) {
        std::cout << prompt;
        int value = 0;
        if (std::cin >> value) {
            if (value >= minValue && value <= maxValue) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::cout << "Value must be between " << minValue << " and " << maxValue << ". Try again.\n";
        } else {
            std::cout << "Invalid integer input. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

double readDouble(const std::string& prompt, double minValue, double maxValue) {
    while (true) {
        std::cout << prompt;
        double value = 0.0;
        if (std::cin >> value) {
            if (value >= minValue && value <= maxValue) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::cout << "Value must be between " << minValue << " and " << maxValue << ". Try again.\n";
        } else {
            std::cout << "Invalid floating point input. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string readString(const std::string& prompt, bool allowEmpty = false) {
    while (true) {
        std::cout << prompt;
        std::string value = "";
        std::getline(std::cin, value);
        if (!value.empty() || allowEmpty) {
            return value;
        }
        std::cout << "Input cannot be empty. Try again.\n";
    }
}

std::string readColor(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string value = "";
        std::getline(std::cin, value);
        if (Validator::isValidColor(value)) {
            return value;
        }
        std::cout << "Invalid color format. Use HEX (#RGB, #RRGGBB) or named color (e.g. red, blue, none). Try again.\n";
    }
}

void handleTask1() {
    std::cout << "\n--- Task 1: Transformed Rectangle (Rect) ---\n";
    double canvasW = readDouble("Canvas width (px): ", 10.0, 10000.0);
    double canvasH = readDouble("Canvas height (px): ", 10.0, 10000.0);
    double vbMinX = readDouble("ViewBox min-x (px, default 0): ", -10000.0, 10000.0);
    double vbMinY = readDouble("ViewBox min-y (px, default 0): ", -10000.0, 10000.0);
    double vbW = readDouble("ViewBox width (px): ", 10.0, 10000.0);
    double vbH = readDouble("ViewBox height (px): ", 10.0, 10000.0);

    double cx = readDouble("Center X coordinate (cx): ", -10000.0, 10000.0);
    double cy = readDouble("Center Y coordinate (cy): ", -10000.0, 10000.0);
    double w = readDouble("Rectangle width (w): ", 1.0, 10000.0);
    double h = readDouble("Rectangle height (h): ", 1.0, 10000.0);
    double rx = readDouble("Corner radius rx (>=0): ", 0.0, 1000.0);
    double ry = readDouble("Corner radius ry (>=0): ", 0.0, 1000.0);
    double angle = readDouble("Rotation angle in degrees: ", -3600.0, 3600.0);

    std::string fill = readColor("Fill color: ");
    std::string stroke = readColor("Stroke color: ");
    double strokeW = readDouble("Stroke width: ", 0.0, 100.0);
    double opacity = readDouble("Opacity (0.0 - 1.0): ", 0.0, 1.0);

    std::string filename = readString("Output SVG filename: ");

    Rect rect = Rect::fromCenter(cx, cy, w, h, rx, ry);
    rect.setFill(fill);
    rect.setStroke(stroke);
    rect.setStrokeWidth(strokeW);
    rect.setOpacity(opacity);

    std::ostringstream transformSs;
    transformSs << "rotate(" << angle << ", " << cx << ", " << cy << ")";
    rect.setTransform(transformSs.str());

    SVGDocumentBuilder builder;
    builder.setCanvas(canvasW, canvasH)
           .setViewBox(vbMinX, vbMinY, vbW, vbH)
           .addElement(std::make_unique<Rect>(rect));

    SVGDocument doc = builder.build();
    if (doc.saveToFile(filename)) {
        std::cout << "[Success] File saved to " << filename << "\n";
    } else {
        std::cout << "[Error] Failed to write file " << filename << "\n";
    }
}

void handleTask2() {
    std::cout << "\n--- Task 2: Hierarchical Groups (Composite Pattern) ---\n";
    double canvasW = readDouble("Canvas width (px): ", 10.0, 10000.0);
    double canvasH = readDouble("Canvas height (px): ", 10.0, 10000.0);
    int nestingLevels = readInt("Nesting levels N (>= 2): ", 2, 20);
    double scaleStep = readDouble("Scale factor per level (e.g. 0.8): ", 0.1, 1.5);
    double shiftStep = readDouble("Shift step per level (e.g. 20.0): ", -500.0, 500.0);

    double mainDx = readDouble("Main group translate dx: ", -5000.0, 5000.0);
    double mainDy = readDouble("Main group translate dy: ", -5000.0, 5000.0);
    double mainAngle = readDouble("Main group rotation angle: ", -3600.0, 3600.0);

    std::string filename = readString("Output SVG filename: ");

    auto rootGroup = std::make_unique<Group>();
    std::ostringstream rootTrans;
    rootTrans << "translate(" << mainDx << ", " << mainDy << ") rotate(" << mainAngle << ")";
    rootGroup->setTransform(rootTrans.str());

    Group* currentGroup = rootGroup.get();

    double baseSize = 200.0;
    for (int i = 0; i < nestingLevels; ++i) {
        double currentSize = baseSize * std::pow(scaleStep, static_cast<double>(i));
        auto r = std::make_unique<Rect>(-currentSize / 2.0, -currentSize / 2.0, currentSize, currentSize, 10.0, 10.0);
        r->setFill("none");
        r->setStroke(i % 2 == 0 ? "#2563eb" : "#dc2626");
        r->setStrokeWidth(2.0);
        r->setOpacity(1.0 - static_cast<double>(i) * 0.04);
        currentGroup->add(std::move(r));

        auto c = std::make_unique<Circle>(0.0, 0.0, currentSize / 3.0);
        c->setFill(i % 2 == 0 ? "#93c5fd" : "#fca5a5");
        c->setOpacity(0.35);
        currentGroup->add(std::move(c));

        if (i + 1 < nestingLevels) {
            auto nextGroup = std::make_unique<Group>();
            std::ostringstream childTrans;
            childTrans << "translate(" << shiftStep << ", " << shiftStep << ") rotate(15)";
            nextGroup->setTransform(childTrans.str());
            Group* nextGroupPtr = nextGroup.get();
            currentGroup->add(std::move(nextGroup));
            currentGroup = nextGroupPtr;
        }
    }

    SVGDocumentBuilder builder;
    builder.setCanvas(canvasW, canvasH)
           .setViewBox(0.0, 0.0, canvasW, canvasH)
           .addElement(std::move(rootGroup));

    SVGDocument doc = builder.build();
    if (doc.saveToFile(filename)) {
        std::cout << "[Success] File saved to " << filename << "\n";
    } else {
        std::cout << "[Error] Failed to write file " << filename << "\n";
    }
}

void handleTask3() {
    std::cout << "\n--- Task 3: Arbitrary Paths and Bezier Curves ---\n";
    double canvasW = readDouble("Canvas width (px): ", 10.0, 10000.0);
    double canvasH = readDouble("Canvas height (px): ", 10.0, 10000.0);

    double x0 = readDouble("Start point x0: ", -10000.0, 10000.0);
    double y0 = readDouble("Start point y0: ", -10000.0, 10000.0);

    double x1 = readDouble("Cubic control point 1 x1: ", -10000.0, 10000.0);
    double y1 = readDouble("Cubic control point 1 y1: ", -10000.0, 10000.0);
    double x2 = readDouble("Cubic control point 2 x2: ", -10000.0, 10000.0);
    double y2 = readDouble("Cubic control point 2 y2: ", -10000.0, 10000.0);
    double x3 = readDouble("Cubic end point x3: ", -10000.0, 10000.0);
    double y3 = readDouble("Cubic end point y3: ", -10000.0, 10000.0);

    int closeChoice = readInt("Close path with Z? (1 = yes, 0 = no): ", 0, 1);
    bool shouldClose = (closeChoice == 1);

    std::string strokeColor = readColor("Stroke color: ");
    double strokeW = readDouble("Stroke width: ", 0.1, 50.0);
    std::string fillColor = readColor("Fill color: ");

    std::string dashArray = readString("stroke-dasharray (e.g. 5,5 or leave empty): ", true);
    std::string lineCap = readString("stroke-linecap (round, square, butt or leave empty): ", true);
    std::string lineJoin = readString("stroke-linejoin (round, bevel, miter or leave empty): ", true);

    std::string filename = readString("Output SVG filename: ");

    Path path;
    path.moveTo(x0, y0);
    path.cubicTo(x1, y1, x2, y2, x3, y3);

    double qx1 = (x3 + x0) / 2.0;
    double qy1 = y3 + 80.0;
    double qx2 = x0;
    double qy2 = y0;
    path.quadTo(qx1, qy1, qx2, qy2);

    if (shouldClose) {
        path.closePath();
    }

    path.setStroke(strokeColor);
    path.setStrokeWidth(strokeW);
    path.setFill(fillColor);
    if (!dashArray.empty()) {
        path.setStrokeDashArray(dashArray);
    }
    if (!lineCap.empty()) {
        path.setStrokeLineCap(lineCap);
    }
    if (!lineJoin.empty()) {
        path.setStrokeLineJoin(lineJoin);
    }

    SVGDocumentBuilder builder;
    builder.setCanvas(canvasW, canvasH)
           .setViewBox(0.0, 0.0, canvasW, canvasH)
           .addElement(std::make_unique<Path>(path));

    SVGDocument doc = builder.build();
    if (doc.saveToFile(filename)) {
        std::cout << "[Success] File saved to " << filename << "\n";
    } else {
        std::cout << "[Error] Failed to write file " << filename << "\n";
    }
}

void handleVariant2() {
    std::cout << "\n--- Variant 2: Isometric Chessboard with Composite and <use> ---\n";
    double canvasW = readDouble("Canvas width (px): ", 100.0, 10000.0);
    double canvasH = readDouble("Canvas height (px): ", 100.0, 10000.0);

    int rows = readInt("Board rows N (e.g. 8): ", 1, 64);
    int cols = readInt("Board columns M (e.g. 8): ", 1, 64);
    double cellSize = readDouble("Cell size (px, e.g. 50): ", 5.0, 500.0);

    std::string whiteColor = readColor("White cells fill color (e.g. #f0d9b5): ");
    std::string blackColor = readColor("Black cells fill color (e.g. #b58863): ");
    std::string strokeColor = readColor("Cell border stroke color (e.g. #2d3748): ");
    double strokeW = readDouble("Cell border stroke width: ", 0.0, 20.0);

    double angle = readDouble("Isometric rotation angle (degrees, standard 45): ", -360.0, 360.0);
    double scaleY = readDouble("Isometric vertical scale (standard 0.5): ", 0.05, 5.0);

    double boardPixelWidth = static_cast<double>(cols) * cellSize;
    double boardPixelHeight = static_cast<double>(rows) * cellSize;

    double defaultDx = canvasW / 2.0;
    double defaultDy = canvasH / 2.0;
    std::cout << "Suggested center translation: dx = " << defaultDx << ", dy = " << defaultDy << "\n";

    double dx = readDouble("Translation dx: ", -10000.0, 10000.0);
    double dy = readDouble("Translation dy: ", -10000.0, 10000.0);

    std::string filename = readString("Output SVG filename: ");

    SVGDocumentBuilder builder;
    builder.setCanvas(canvasW, canvasH)
           .setViewBox(0.0, 0.0, canvasW, canvasH);

    std::ostringstream whiteDef;
    whiteDef << "<rect id=\"cell_white\" width=\"" << cellSize << "\" height=\"" << cellSize
             << "\" fill=\"" << whiteColor << "\" stroke=\"" << strokeColor
             << "\" stroke-width=\"" << strokeW << "\"/>";
    builder.addDef(whiteDef.str());

    std::ostringstream blackDef;
    blackDef << "<rect id=\"cell_black\" width=\"" << cellSize << "\" height=\"" << cellSize
             << "\" fill=\"" << blackColor << "\" stroke=\"" << strokeColor
             << "\" stroke-width=\"" << strokeW << "\"/>";
    builder.addDef(blackDef.str());

    auto rootBoardGroup = std::make_unique<Group>();
    rootBoardGroup->setId("chessboard_root");

    std::ostringstream rootTransform;
    rootTransform << "translate(" << dx << ", " << dy << ") "
                  << "scale(1.0, " << scaleY << ") "
                  << "rotate(" << angle << ") "
                  << "translate(" << (-boardPixelWidth / 2.0) << ", " << (-boardPixelHeight / 2.0) << ")";
    rootBoardGroup->setTransform(rootTransform.str());

    auto whiteGroup = std::make_unique<Group>();
    whiteGroup->setId("white_cells_group");

    auto blackGroup = std::make_unique<Group>();
    blackGroup->setId("black_cells_group");

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            double cellX = static_cast<double>(c) * cellSize;
            double cellY = static_cast<double>(r) * cellSize;

            if ((r + c) % 2 == 0) {
                auto cellUse = std::make_unique<Use>("#cell_white", cellX, cellY);
                whiteGroup->add(std::move(cellUse));
            } else {
                auto cellUse = std::make_unique<Use>("#cell_black", cellX, cellY);
                blackGroup->add(std::move(cellUse));
            }
        }
    }

    rootBoardGroup->add(std::move(whiteGroup));
    rootBoardGroup->add(std::move(blackGroup));

    builder.addElement(std::move(rootBoardGroup));

    SVGDocument doc = builder.build();
    if (doc.saveToFile(filename)) {
        std::cout << "[Success] Chessboard successfully saved to " << filename << "\n";
    } else {
        std::cout << "[Error] Failed to write file " << filename << "\n";
    }
}

int main() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== SVG Vector Graphics Generator (C++17) ===\n";
        std::cout << "1. Transformed Rectangle (Rect)\n";
        std::cout << "2. Hierarchical Nested Groups (Composite Pattern)\n";
        std::cout << "3. Curved Path Generation (Path with Bezier)\n";
        std::cout << "4. Variant 2: Isometric Chessboard (<use> & Composite)\n";
        std::cout << "0. Exit\n";

        choice = readInt("Select menu option: ", 0, 4);

        switch (choice) {
            case 1:
                handleTask1();
                break;
            case 2:
                handleTask2();
                break;
            case 3:
                handleTask3();
                break;
            case 4:
                handleVariant2();
                break;
            case 0:
                std::cout << "Exiting program. Goodbye!\n";
                break;
            default:
                break;
        }
    }
    return 0;
}
