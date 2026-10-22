# Lane Detection

Python script that captures the left half of a 1920x1080 screen, detects white and yellow lane lines, and presses `a` or `d` when the lane lines reach a trapezoid-shaped zone in front of the "car." Built for steering in a game window.

## Requirements

- Python 3
- Libraries: `opencv-python`, `numpy`, `mss`, `Pillow`, `keyboard`

```
pip install opencv-python numpy mss Pillow keyboard
```

The `keyboard` library may need administrator (Windows) or root (Linux) rights to send key presses.

## Setup

1. Set your display to **1920x1080**. If it's different, change `screen_width` and `screen_height` in both `lane_detection_process` and the `__main__` block.
2. Put the game or video in the **left half** of the screen. The script captures the region starting at the top-left corner (0, 0) that is 960 pixels wide and 1080 pixels tall.
3. Run the script:

   ```
   python <script name>.py
   ```
4. A "Lane Detection" window opens showing the capture with the detected lines drawn on it.

## Quitting

1. Click the "Lane Detection" window so it has focus.
2. Press **q**. The window closes and lane detection stops.
3. If the terminal doesn't return to the prompt, press **Ctrl+C** in the terminal to stop the key-pressing process too.

Pressing `q` only works while the "Lane Detection" window is focused, not from any other window.

## How It Works

The script runs two processes that share two flags (`purple_intersects_red` and `purple_intersects_blue`).

**Process 1: lane detection** (`lane_detection_process`)

1. Grabs the left half of the screen with `mss` and converts it to a BGR image.
2. Converts to HSV and keeps only white and yellow pixels:

   | Color  | HSV lower        | HSV upper         |
   |--------|------------------|-------------------|
   | White  | (0, 0, 200)      | (180, 25, 255)    |
   | Yellow | (20, 100, 100)   | (30, 255, 255)    |

3. Blurs the mask (5x5 Gaussian) and runs Canny edge detection (thresholds 50 and 150).
4. Keeps only edges inside a trapezoid in the bottom half of the capture. For the default 960x1080 capture, its corners are:

   | Corner       | Position (x, y) |
   |--------------|-----------------|
   | Top left     | (462, 540)      |
   | Top right    | (742, 540)      |
   | Bottom right | (942, 1080)     |
   | Bottom left  | (262, 1080)     |

   The trapezoid is outlined in green on the display window.
5. Finds line segments with the Hough transform (`threshold=20`, `minLineLength=80`, `maxLineGap=300`).
6. Ignores lines with a slope between -0.5 and 0.5. Of the rest, the **longest line with a negative slope** is the left lane (drawn in red) and the **longest line with a positive slope** is the right lane (drawn in blue).
7. Sets a flag when the lane has been found and any corner of the trapezoid falls within 10 pixels of a detected line's bounding box.

**Process 2: key pressing** (`key_pressing_process`)

| Flag                       | Key pressed | Hold time | Wait after |
|----------------------------|-------------|-----------|------------|
| Left lane (red) touching   | `d`         | 0.05 s    | 1 s        |
| Right lane (blue) touching | `a`         | 0.05 s    | 1 s        |

So the script steers away from whichever lane line the trapezoid reaches, and can steer at most about once per second.

## Tuning

| What to change                  | Where                                              | Default |
|---------------------------------|----------------------------------------------------|---------|
| Move the trapezoid left/right   | `shift_amount` (negative moves it right)           | `-122`  |
| Trapezoid bottom width          | `bottom_width`                                     | `width // 2 + 200` |
| Trapezoid top width             | `top_width`                                        | `width // 2 - 200` |
| Trapezoid height                | `trapezoid_height`                                 | `height // 2` |
| How close counts as touching    | `tolerance` in `detect_lanes`                      | `10` px |
| Minimum slope for a lane line   | `slope_threshold` in `detect_lanes`                | `0.5`   |
| Key hold time                   | first `time.sleep()` after each `keyboard.press`   | `0.05` s |
| Time between steering presses   | second `time.sleep()` after each `keyboard.release`| `1` s   |

The trapezoid is calculated in two places (`detect_lanes` and the `__main__` block), so change `shift_amount` and the width and height values in both.
