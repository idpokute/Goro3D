#include "GameLib/Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
#include "GameLib/Math.h"
#include "Core/VertexBuffer.h"
#include "Core/IndexBuffer.h"
#include "Core/Batch.h"
#include "Core/Model.h"
#include "Core/Camera.h"

#include "Core/Document.h"

#include "Core/Matrix34.h"
#include "Core/Matrix44.h"
#include "Core/Pad.h"

#include "Core/Element.h"
#include "Core/GraphicData.h"

int g_cnt = 0;
Camera camera;
GraphicData* g_ResourceStage;
GraphicData* g_ResourceRobot;
Model* g_Model[2];

namespace GameLib{
    bool bFirstFrame = true;

    void Framework::update()
    {
        if( bFirstFrame )
        {
            Pad::Create();
            bFirstFrame = false;
            g_ResourceStage = new GraphicData("data.txt");
            g_ResourceRobot = new GraphicData("robo.txt");
            g_Model[0] = g_ResourceRobot->CreateModel("robo");
            g_Model[1] = g_ResourceRobot->CreateModel("robo");

            Document doc;
            Element* root = doc.GetRoot();
            Element* tmp = new Element("Test");
            double p[3] = { 10,0,-10 };

            Attribute* a = new Attribute("Pos", "1,1,1");
            a->Set("Hehe",p,3);
            tmp->AddAttribute(a);
            root->AddElement(tmp);
            doc.Write("MyFirst.txt");
        }
        setFrameRate( 60 );
        g_cnt++;
        
        // View matrix 
        //camera.SetPos( Vector3(sin(g_cnt)*10, 1, cos(g_cnt)*10) );
        camera.SetPos( Vector3(0, 1, 10) );
        camera.SetTarget( Vector3(0,0,0) );
 
        Matrix44 matProjView;
        camera.CreateProjViewMatrix(&matProjView);        

        g_ResourceStage->GetBatch("batch")->Draw(matProjView);
        g_Model[0]->SetPos(Vector3(2,0,0));
        g_Model[0]->Draw(matProjView);

        g_Model[1]->SetPos(Vector3(-2,1,0));
        g_Model[1]->SetScale(Vector3(2,1,2));
        g_Model[1]->Draw(matProjView);

        enableDepthTest( true );

        if ( isEndRequested() ){            			
            SAFE_DELETE( g_ResourceStage );
            SAFE_DELETE( g_ResourceRobot );
            Pad::Destroy();
		}
    }
}


