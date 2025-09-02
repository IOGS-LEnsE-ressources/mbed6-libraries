import cv2

name = input('Name of the initial image')
image = cv2.imread(f'./Images/{name}.pbm', cv2.IMREAD_UNCHANGED)

w, h = 200, 120

for y in range(0, image.shape[0], h):
    for x in range(0, image.shape[1], w):
        sub_image = image[y:y+h, x:x+w]
        cv2.imwrite(f"./Images/{name}_{y}_{x}.pbm", sub_image)