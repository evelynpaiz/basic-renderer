#pragma once

using MouseCode = unsigned int;

namespace Mouse
{
/**
 * @brief Enumeration of mouse codes conventions.
 *
 * The `Mouse` namespace provides an enumeration of mouse codes representing different mouse buttons.
 * These codes can be used to identify and handle specific mouse input in the application.
 */
enum : MouseCode
{
    // From glfw3.h
    // ----------------------------------------
    Button0 = 0,            ///< The first mouse button
    Button1 = 1,            ///< The second mouse button
    Button2 = 2,            ///< The third mouse button
    Button3 = 3,            ///< The fourth mouse button
    Button4 = 4,            ///< The fifth mouse button
    Button5 = 5,            ///< The sixth mouse button
    Button6 = 6,            ///< The seventh mouse button
    Button7 = 7,            ///< The eighth mouse button

    ButtonLast = Button7,   ///< The last mouse button
    ButtonLeft = Button0,   ///< The left mouse button
    ButtonRight = Button1,  ///< The right mouse button
    ButtonMiddle = Button2  ///< The middle mouse button
};
} // namespace Mouse

