#include <BigModelManager.h>
#include <DataManager.h>
#include <Scene.h>
#include <iostream>
#include <my_exception.h>
#include <typeinfo>
BigModelManager::BigModelManager()
{
}
void BigModelManager::callDataManager(string sourceName)
{
    ConcreteDataManager data(sourceName);
    PrototypeModel* temp = nullptr;
    temp = data.getModel();
    scene.addElement(temp);
}
void BigModelManager::setSceneObjectManager(pick action)
{

    switch(action)
    {
    case(pick::pick_mash):{
        break;

    }

    }

}
