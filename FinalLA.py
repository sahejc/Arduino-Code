import cv2
import numpy as np
import mss
from PIL import Image
import keyboard
import time
import multiprocessing

def region_of_interest(img, vertices):
    mask = np.zeros_like(img)
    cv2.fillPoly(mask, vertices, 255)
    masked_img = cv2.bitwise_and(img, mask)
    return masked_img

def detect_lanes(img,roi_vertices):
    hsv_img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    white_lower = np.array([0, 0, 200], dtype=np.uint8)
    white_upper = np.array([180, 25, 255], dtype=np.uint8)
    yellow_lower = np.array([20, 100, 100], dtype=np.uint8)
    yellow_upper = np.array([30, 255, 255], dtype=np.uint8)

    white_mask = cv2.inRange(hsv_img, white_lower, white_upper)
    yellow_mask = cv2.inRange(hsv_img, yellow_lower, yellow_upper)
    color_mask = cv2.bitwise_or(white_mask, yellow_mask)

    blurred_img = cv2.GaussianBlur(color_mask, (5, 5), 0)

    edges = cv2.Canny(blurred_img, 50, 150)

    height, width = img.shape[:2]
    bottom_width = width // 2 + 200  # Adjust the bottom width as needed
    top_width = width // 2 - 200    # Adjust the top width as needed
    trapezoid_height = height // 2  # Adjust the trapezoid height as needed

    shift_amount = -122
    roi_vertices = np.array([[(width // 2 - top_width // 2 - shift_amount, height // 2),
                             (width // 2 + top_width // 2 - shift_amount, height // 2),
                             (width // 2 + bottom_width // 2 - shift_amount, height // 2 + trapezoid_height),
                             (width // 2 - bottom_width // 2 - shift_amount, height // 2 + trapezoid_height)]], dtype=np.int32)
    vertices = roi_vertices
    roi_img = region_of_interest(edges, vertices)

    # Draw ROI outline on the output image
    roi_outline_color = (0, 255, 0)  # Green color for ROI outline
    cv2.polylines(img, vertices, isClosed=True, color=roi_outline_color, thickness=2)

    # Lane detection using Hough transform
    lines = cv2.HoughLinesP(roi_img, 1, np.pi/180, threshold=20, minLineLength=80, maxLineGap=300)

    left_line = None
    right_line = None

    if lines is not None:
        for line in lines:
            x1, y1, x2, y2 = line[0]
            slope = (y2 - y1) / (x2 - x1 + 1e-6)
            slope_threshold = 0.5
            if abs(slope) > slope_threshold:
                if slope < 0:
                    # Calculate the length of the line using the Euclidean distance formula
                    line_length = np.sqrt((x2 - x1)**2 + (y2 - y1)**2)
                    if left_line is None or line_length > left_line[1]:
                        left_line = (line, line_length)
                else:
                    # Calculate the length of the line using the Euclidean distance formula
                    line_length = np.sqrt((x2 - x1)**2 + (y2 - y1)**2)
                    if right_line is None or line_length > right_line[1]:
                        right_line = (line, line_length)

    line_img = np.zeros_like(img)
    if left_line is not None:
        x1, y1, x2, y2 = left_line[0][0]
        cv2.line(line_img, (x1, y1), (x2, y2), (0, 0, 255), 3)  # Longest Left lane (red)
    if right_line is not None:
        x1, y1, x2, y2 = right_line[0][0]
        cv2.line(line_img, (x1, y1), (x2, y2), (255, 0, 0), 3)  # Longest Right lane (blue)

    # Convert the original image to grayscale
    gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

   
    # Check if the purple trapezoid touches the red line (left lane)
    purple_intersects_red = False
    tolerance = 10  # Adjust the tolerance value as needed

    if left_line is not None:
        for line in lines:
            x1, y1, x2, y2 = line[0]
            # Check if any of the trapezoid vertices is inside the bounding box of the line
            if (x1 - tolerance <= roi_vertices[0][0][0] <= x2 + tolerance and y1 - tolerance <= roi_vertices[0][0][1] <= y2 + tolerance) or \
               (x1 - tolerance <= roi_vertices[0][1][0] <= x2 + tolerance and y1 - tolerance <= roi_vertices[0][1][1] <= y2 + tolerance) or \
               (x1 - tolerance <= roi_vertices[0][2][0] <= x2 + tolerance and y1 - tolerance <= roi_vertices[0][2][1] <= y2 + tolerance) or \
               (x1 - tolerance <= roi_vertices[0][3][0] <= x2 + tolerance and y1 - tolerance <= roi_vertices[0][3][1] <= y2 + tolerance):
                purple_intersects_red = True
                break


   # Check if the purple trapezoid touches the blue line (right lane)
    purple_intersects_blue = False

    if right_line is not None:
        for line in lines:
         x1, y1, x2, y2 = line[0]
         # Check if any of the trapezoid vertices is inside the bounding box of the line
         if (x1 - tolerance <= roi_vertices[0][0][0] <= x2 + tolerance and y1 - tolerance <= roi_vertices[0][0][1] <= y2 + tolerance) or \
            (x1 - tolerance <= roi_vertices[0][1][0] <= x2 + tolerance and y1 - tolerance <= roi_vertices[0][1][1] <= y2 + tolerance) or \
            (x1 - tolerance <= roi_vertices[0][2][0] <= x2 + tolerance and y1 - tolerance <= roi_vertices[0][2][1] <= y2 + tolerance) or \
            (x1 - tolerance <= roi_vertices[0][3][0] <= x2 + tolerance and y1 - tolerance <= roi_vertices[0][3][1] <= y2 + tolerance):
             purple_intersects_blue = True
             break

    
   


    # Combine the lane lines and black regions with the original image
    result = cv2.addWeighted(img, 0.8, line_img, 1, 0)

    return result, purple_intersects_red, purple_intersects_blue

def lane_detection_process(roi_vertices, purple_red, purple_blue):
    # Initialize the mss screen capture object
    screen_capture = mss.mss()

    while True:
        
        screen_width, screen_height = 1920, 1080

        # Capture a screen frame (left half of the screen)
        screenshot = screen_capture.grab({"top": 0, "left": 0, "width": screen_width // 2, "height": screen_height})
        frame = np.array(Image.frombytes("RGB", screenshot.size, screenshot.bgra, "raw", "BGRX"))

        # Perform lane detection on the captured frame
        result_frame, purple_intersects_red, purple_intersects_blue = detect_lanes(frame, roi_vertices)

        # Update the shared variables
        purple_red.value = purple_intersects_red
        purple_blue.value = purple_intersects_blue

        # Display the processed frame with lane detection
        cv2.imshow('Lane Detection', result_frame)

        # Check if the user presses 'q' to exit the loop
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cv2.destroyAllWindows()

def key_pressing_process(purple_red, purple_blue):
    while True:
        # Simulate 'd' key press for 200 milliseconds if purple trapezoid touches the red line
        if purple_red.value:
            keyboard.press('d')
            time.sleep(0.05)
            keyboard.release('d')
            time.sleep(1)

        # Simulate 'a' key press for 200 milliseconds if purple trapezoid touches the blue line
        if purple_blue.value:
            keyboard.press('a')
            time.sleep(0.05)
            keyboard.release('a')
            time.sleep(1)

        
        

if __name__ == "__main__":
    # Set the screen capture dimensions (adjust as needed)
    screen_width, screen_height = 1920, 1080

    height, width = screen_height, screen_width // 2
    bottom_width = width // 2 + 200  # Adjust the bottom width as needed
    top_width = width // 2 - 200    # Adjust the top width as needed
    trapezoid_height = height // 2  # Adjust the trapezoid height as needed


    shift_amount = -122
    roi_vertices = np.array([[(width // 2 - top_width // 2 - shift_amount, height // 2),
                             (width // 2 + top_width // 2 - shift_amount, height // 2),
                             (width // 2 + bottom_width // 2 - shift_amount, height // 2 + trapezoid_height),
                             (width // 2 - bottom_width // 2 - shift_amount, height // 2 + trapezoid_height)]], dtype=np.int32)

    # Create shared variables for inter-process communication
    purple_intersects_red = multiprocessing.Value('i', 0)
    purple_intersects_blue = multiprocessing.Value('i', 0)

    # Create processes for lane detection and key pressing
    lane_detection_proc = multiprocessing.Process(target=lane_detection_process, args=(roi_vertices, purple_intersects_red, purple_intersects_blue))
    key_pressing_proc = multiprocessing.Process(target=key_pressing_process, args=(purple_intersects_red, purple_intersects_blue))

    # Start the processes
    lane_detection_proc.start()
    key_pressing_proc.start()

    # Wait for both processes to finish
    lane_detection_proc.join()
    key_pressing_proc.join()