#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

int x[20], y[20], n = 0, filled = 0;

void drawPolygon(){
	glColor3f(1.0,1.0,1.0);
	glLineWidth(2.0);

	glBegin(GL_LINE_LOOP);
	for(int i=0; i<n; i++)
		glVertex2i(x[i], y[i]);
	glEnd();
}

void scanLineFill(){
	int ymin = y[0], ymax = y[0];
	int intersections[20];
	

	for(int i=1; i<n; i++){
		if(y[i]<ymin) ymin = y[i];
		if(y[i]>ymax) ymax = y[i];
	}
	glColor3f(0.0,1.0,1.0);

	for(int i=ymin; i<ymax; i++){
		int k=0;
		for(int j=0; j<n; j++){
			int next = (j+1) %n;

			if((y[j]<=i && y[next]>i) || (y[j]>i && y[next]<=i))
					intersections[k++] = x[j] + (int) ((double) (i-y[j]) * (x[next]-x[j]) / (y[next]-y[j]));
		}

		for(int j=0; j<k-1; j++){
			for(int m = j+1; m<k; m++){
				if(intersections[j] > intersections[m]){
					int temp = intersections[j];
					intersections[j] = intersections[m];
					intersections[m] = temp;
				}
			}
		}

		glBegin(GL_LINES);
		for(int j=0; j+1<k; j+=2){
			glVertex2i(intersections[j], i);
			glVertex2i(intersections[j+1], i);
		}
		glEnd();
	}

}

void init(){
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,800,0,600);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void menu(int choice){
	if(choice == 1) filled = 1;
	if(choice == 2) filled = 0;

	glutPostRedisplay();
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	if(filled)
		scanLineFill();
	drawPolygon();
	glFlush();
}

int main(int argc, char** argv){
	printf("Enter number of verices: ");
	scanf("%d", &n);

	for(int i=0; i<n; i++){
		printf("Enter point %d : ", i+1);
		scanf("%d %d", &x[i], &y[i]);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);

	glutCreateWindow("Scan Line Algorithm");

	init();

	glutCreateMenu(menu);
	glutAddMenuEntry("1. Fill Polygon", 1);
	glutAddMenuEntry("2. Clear Fill ", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}



