class Application {
	
	private:
		
	vector<Punto> puntos;
	vector<Linea> lineas;
	vector<Curva> curvas;
		

    public:
    	
    void agregarPunto(Punto punto)
    {
    	puntos.push_back(punto);
	}
	
	void agregarLinea(Linea linea)
    {
    	lineas.push_back(linea);
	}
	
	void agregarCurva(Curva curva)
	{
		curvas.push_back(curva);
	}
	
	void dibujarPuntos()
	{
		for(int i = 0; i < puntos.size();i++)
		{
			puntos[i].draw();
		}
	}
	
	void dibujarLineas()
	{
		for(int i = 0; i < lineas.size();i++)
		{
			lineas[i].draw();
		}
	}
	
	void dibujarCurvas()
	{
		for(int i = 0; i < curvas.size();i++)
		{
			curvas[i].bezier();
			//curvas[i].bsplineCubica();
		}
	}
	
	void eliminarPuntos()
	{
		puntos.clear();
	}
	
	void eliminarLineas()
	{
		lineas.clear();
	}
	
	void eliminarCurvas()
	{
		curvas.clear();
	}
	
	void eliminarUltimaLinea()
	{
		if(lineas.size()>0){
			lineas.pop_back();
		}
	}
	
	void eliminarUltimaCurva()
	{
		if(curvas.size()>0){
			curvas.pop_back();
		}
	}
    	
    static Application* Instance()
	{
		static Application app;
		return &app;
	}	

};


    

