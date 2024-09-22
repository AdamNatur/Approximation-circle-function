# Approximation-circle-function
In this project I developed a Dialog-based MFC application to realize finding the diameter and deviation from roundness of a sphere. It takes the coordinates of points from the text file *.tat, which generated using the file “Task Generator” (columns x* and y* pre-set Xc, Yc, R). The data file specifying created with using the standard file opening dialog (class CFileDialog). The permissible error is 0.00001. In the "perfect" nominal case coordinates of circle center and radius are x = 5, y = 4, z = 6, R = 3. But with using file “Task Generator” coordinates of points get "dirty"with random deviations. So, the program founds parameters of new "dirty" sphere and compares with perfect one.

Application preview.

![image](https://github.com/user-attachments/assets/6ea30ab4-68ef-4be8-aa26-4abb0af65cee)

By clicking on the button "Open file", we run file explorer dialog box and specifying data by choosing file we need.

![image](https://github.com/user-attachments/assets/a2d36b1d-b78a-4a89-bad4-3a00dee8ade5)

Then we get file data - filename and path to.

Below the program shows us result of evaluation : roundness deviation and parameter of evaluated sphere.

So, for testing that program works we can specify data of perfect coordinates and see result.

![image](https://github.com/user-attachments/assets/4ab9b09b-3ff4-42f0-ada4-f95874526bba)

We can see that program evaluated perfect values correctly.




