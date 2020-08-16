#include <math.h>
class Punto{
	private:
		GLint x = 0,y = 0;
		GLfloat r = 0.0,g = 1.0,b = 0.0;
		float PI = 3.1415926475;
	public :
		Punto(){
			x = 0,y = 0;
		}
		Punto(GLint x_,GLint y_){
			x = x_;
			y = y_;			
		}
		Punto(GLint x_,GLint y_,GLfloat r_,GLfloat g_,GLfloat b_){
			x = x_;
			y = y_;
			r = r_;
			g = g_;
			b = b_;	
		}
		GLint getx(){
			return x;
		}
		GLint gety(){
			return y;
		}
		void setx(GLint x_){
			x = x_;
		}
		void sety(GLint y_){
			y = y_;
		}
		void setRGB(GLfloat r_,GLfloat g_,GLfloat b_){
			r = r_;
			g = g_;
			b = b_;	
		}
		Punto rotar(float theta){
			theta = theta*PI/180;
			Punto p= Punto(x,y);
			p.setx(x*cos(theta)-y*sin(theta));
			p.sety(x*sin(theta)+y*cos(theta));
			return p;
		}
		Punto trasladar(GLint Tx,GLint Ty){
			Punto p = Punto(x,y);
			p.setx(x+Tx);
			p.sety(y+Ty);
			return p;
		}
		void draw(){
			glBegin(GL_POINTS);
				glColor3f(r,g,b);
				glVertex2d(x,y);
			glEnd();
		}
};

