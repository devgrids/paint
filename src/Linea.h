
class Linea{
	private:
		Punto origen;
		Punto destino;
		GLfloat r = 0.0,g = 1.0,b = 0.0;
	public:
		Linea(Punto o,Punto d){
			origen = o;
			destino = d;
		}
		Linea(Punto o,Punto d,GLfloat r_,GLfloat g_,GLfloat b_){
			origen = o;
			destino = d;
			r = r_;
			g = g_;
			b = b_;
		}
		void draw(){
			glBegin(GL_LINES);
			    glColor3f(r,g,b);
				glVertex2i(origen.getx(),origen.gety());
				glVertex2i(destino.getx(),destino.gety());
			glEnd();
		}
		Linea rotar(float theta){
			Punto origenR = origen.rotar(theta);
			Punto destinoR = destino.rotar(theta);
			Linea L = Linea(origenR,destinoR);
			return L;
		}
		Linea trasladar(GLint Tx,GLint Ty){
			Punto origenT = origen.trasladar(Tx,Ty);
			Punto destinoT = destino.trasladar(Tx,Ty);
			Linea L = Linea(origenT,destinoT);
			return L;
		}
		void dda(){
			Punto punto = Punto();
			glColor3f(r,g,b);
			GLint X0 = origen.getx();
			GLint Y0 = origen.gety();
			GLint X1 = destino.getx();
			GLint Y1 = destino.gety();
			float x,y,xs,ys,dx,dy,steps;
			dx = X1 - X0;
			dy = Y1 - Y0;
			x = X0;
			y = Y0;
			if (abs(dx)>=abs(dy)){
				steps = abs(dx);
			}else{
				steps = abs(dy);
			}
			if (steps==0){
				punto.setx(GLint(X1));
				punto.sety(GLint(Y1));
				punto.draw();
			}else{
				xs = dx/steps;
				ys = dy/steps;
				for(int i = 0;i<=steps;i++){
					punto.setx(GLint(x));
					punto.sety(GLint(y));
					punto.draw();
					x = x + xs;
					y = y + ys;
				}
			}			
		}
};

