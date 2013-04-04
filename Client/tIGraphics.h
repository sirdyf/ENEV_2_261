#pragma once

class tGraphics{
public:
	tGraphics(void);
	virtual ~tGraphics(void);
	virtual Init()=0;
	virtual StartRender()=0;
	virtual EndRender()=0;
	virtual PrintText(x,y,text)=0;
	virtual DrawShip(pos,dir,up,num_obj,rad);
	virtual DrawPlanet(pos,rad);
	virtual DrawLine2D(x,y,x2,y2,color);
	virtual DrawLine3D(Vector pos,Vector pos2,color);
	virtual DrawStarField();
	virtual DrawIndicator(value, x, y, text);
	virtual DrawRadarLabel2D(pos);
	virtual Scene->SetCameraPos();
	virtual Scene->SetCameraOrient();
	virtual Scene->GetViewMatrix();
	virtual Scene->GetWorldMatrix();
	virtual Scane->GetProjectMatrix();
};
