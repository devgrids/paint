class Curva{
	private:
		vector<Punto> puntos;
		int npuntos = 0;
		GLfloat x=0,y=0;
		Punto pt;
		void drawpoligono(){
			glBegin(GL_LINES);
				for(int i = 0;i<npuntos-1;i++){
					glVertex2i(300-puntos[i].getx(),300-puntos[i].gety());
					glVertex2i(300-puntos[i+1].getx(),300-puntos[i+1].gety());	
				}	
			glEnd();
		}
		int factorial(int n){
			int salida = 1;
			for(int i = 1;i<=n;i++){
				salida = salida *i;
			}
			return salida;
		}
		int combinacion(int n,int i){
			int salida = 0;
			if(i==0 || n ==i){
				return 1;
			}else{
				salida = factorial(n)/(factorial(i)*factorial(n-i));
			}
			return salida;
		}
		double pot(double b,int e){
			if (e==0)
				return 1;
			if (e==1){
				return b;
			}
			if (e>1){
				double salida = 1;
				for(int i = 0;i<e;i++){
					salida = salida *b;
				}
				return salida;
			}
		}
		double bernstein(int n, double i,double t){
			return combinacion(n,i)*pot(t,i)*pot(1-t,n-i);
		}
	public:
		Curva(vector<Punto> pts){
			npuntos = pts.size();
			puntos=pts;
			drawpoligono();
		}
		void bezier(){
			for(int j=0;j<=100;j++){
				float t = (float) j/100;
				x = 0;
				y = 0;
				for(int i=0;i<npuntos;i++){
					GLfloat B = bernstein(npuntos-1,i,t);
					x = x + puntos[i].getx()*B;
					y = y + puntos[i].gety()*B;
				}
				pt.setx(x);
				pt.sety(y);
				pt.draw();
			}
		}
	void bsplineCubica(){
		GLfloat x0 =0,y0=0;
		GLfloat x1 =0,y1=0;
		GLfloat x2 =0,y2=0;
		float a0 = 40;
		float a1 = 40;
		float a2 = 60;
		float c0 = 0;
		float b2 = 1.880672269;
		float c2 = -0.050420168;
		float d2 = 0.000336134;
		float b0 = -0.867226891;
		float d0 = 0.000542017;
		float b1 = 1.734453782;
		float c1 = 0.065042017;
		float d1 = -0.003848739;
		for (int j = 0;j<=1000;j++){
			float t = (float)j/1000;
			// P0
			x0 = 20 + t*(60-20);
			y0 = a0 +b0*(x0-20)+c0*(x0-20)*(x0-20)+d0*(x0-20)*(x0-20)*(x0-20);
			pt.setx(GLint(x0));
			pt.sety(GLint(y0));
			pt.setRGB(1,0,0);
			pt.draw();
			
			// P1
			x1 = 60 + t*(70-60);
			y1 = a1 +b1*(x1-60)+c1*(x1-60)*(x1-60)+d1*(x1-60)*(x1-60)*(x1-60);
			pt.setx(GLint(x1));
			pt.sety(GLint(y1));
			pt.setRGB(0,1,0);
			pt.draw();
			
			// P2
			x2 = 70 + t*(120-70);
			y2 = a2 +b2*(x2-70)+c2*(x2-70)*(x2-70)+d2*(x2-70)*(x2-70)*(x2-70);
			pt.setx(GLint(x2));
			pt.sety(GLint(y2));
			pt.setRGB(0,0,1);
			pt.draw();				
		}

	}
	
	
	
	
	
	
	
	
	
	
	
};

