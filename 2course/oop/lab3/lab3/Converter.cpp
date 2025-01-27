#include <Converter.h>
#include <my_exception.h>
//мейн функция
sConvertedPoints* ConcreteConverter1::getConvertedPoints(ConcreteModel1* a, ConcreteCamera1* camera1)
{
    sConvertedPoints* conv = AllocateConvertedPoints(a->vertices); //структура точек на экране

    double* ConvMatrix = GetConversionMatrix(a,camera1); //матрица преобразований

    Convertation(conv, a, ConvMatrix, camera1); //преобразуем точки
    //  return 0;

    delete[] ConvMatrix;

    return conv;
}
//для всех точек конвертируем
void ConcreteConverter1::Convertation(sConvertedPoints*& conv, ConcreteModel1* points, double* ConvMatrix, ConcreteCamera1* camera1)
{
    for (int i = 0; i < points->vertices; i++) {
        sPoint3d temp1;
        temp1.x = points->x[i];
        temp1.y = points->y[i];
        temp1.z = points->z[i];
      //  QPointF point;
     //     point.setX( (temp1.x*camera1->z+temp1.z*camera1->x)/(temp1.z+camera1->z));
       // point.setY((temp1.y*camera1->z+temp1.z*camera1->y)/(temp1.z+camera1->z));
        QPoint point = ConvertSinglePoint(temp1, ConvMatrix);
        conv->Xs[i] = point.x()+camera1->x;
        conv->Ys[i] = point.y();
    }
}
//выделяем память
sConvertedPoints* ConcreteConverter1::AllocateConvertedPoints(int count)
{
    sConvertedPoints* conv = new sConvertedPoints;

    int* Xs = new int[count]; //массив координат Х
    if (!Xs)
        throw memory_alloc_error();
    int* Ys = new int[count]; //массив координат У
    if (!Ys)
        throw memory_alloc_error();

    conv->count = count;
    conv->Xs = Xs;
    conv->Ys = Ys;
}
//получаем матрицу преобразований
double* ConcreteConverter1::GetConversionMatrix(ConcreteModel1* data,ConcreteCamera1 *camera1)
{
    double* ShiftMatrix = mt.Get3DShiftMatrix(data->dx+camera1->x, data->dy+camera1->y, data->dz+camera1->z); //смещение от О
    if (!ShiftMatrix) {
        return nullptr;
    }
    double* RotateZMatrix = mt.Get3DRotateZMatrix(data->fz); //поворот вокруг OZ
    if (!RotateZMatrix) {
        delete ShiftMatrix;
        return nullptr;
    }
    double* RotateYMatrix = mt.Get3DRotateYMatrix(data->fy); //поворот вокруг OY
    if (!RotateYMatrix) {
        delete RotateZMatrix;
        delete ShiftMatrix;
        return nullptr;
    }
    double* RotateXMatrix = mt.Get3DRotateXMatrix(data->fx); //поворот вокруг OX
    if (!RotateXMatrix) {
        delete ShiftMatrix;
        delete RotateYMatrix;
        delete RotateZMatrix;
        return nullptr;
    }
    double* ScaleMatrix = mt.Get3DScaleMatrix(data->M); //масштабировние относительно О
    if (!ScaleMatrix) {
        delete ShiftMatrix;
        delete RotateZMatrix;
        delete RotateYMatrix;
        delete RotateXMatrix;
        return nullptr;
    }

    //матрицы получены - собираем из них исходную

    double* matr1 = mt.MultMatrixXMatrix(ShiftMatrix, RotateZMatrix, 3); //Shift х Z
    if (!matr1) {
        delete ShiftMatrix;
        delete RotateZMatrix;
        delete RotateYMatrix;
        delete RotateXMatrix;
        delete ScaleMatrix;
        return nullptr;
    }
    double* matr2 = mt.MultMatrixXMatrix(matr1, RotateYMatrix, 3); // x Y
    if (!matr2) {
        delete ShiftMatrix;
        delete RotateZMatrix;
        delete RotateYMatrix;
        delete RotateXMatrix;
        delete ScaleMatrix;
        delete matr1;
        return nullptr;
    }
    double* matr3 = mt.MultMatrixXMatrix(matr2, RotateXMatrix, 3); //x X
    if (!matr3) {
        delete ShiftMatrix;
        delete RotateZMatrix;
        delete RotateYMatrix;
        delete RotateXMatrix;
        delete ScaleMatrix;
        delete matr2;
        delete matr1;
        return nullptr;
    }
    double* res = mt.MultMatrixXMatrix(matr3, ScaleMatrix, 3); //x Scale
    if (!res) {
        delete ShiftMatrix;
        delete RotateZMatrix;
        delete RotateYMatrix;
        delete RotateXMatrix;
        delete ScaleMatrix;
        delete matr1;
        delete matr2;
        delete matr3;
        return nullptr;
    }
    //мда
    /* delete ShiftMatrix;
    delete RotateZMatrix;
    delete RotateYMatrix;
    delete RotateXMatrix;
    delete ScaleMatrix;
    delete matr1;
    delete matr2;
    delete matr3;*/

    return res;
}

//умножение вектора на матрицу
double* ConcreteConverter1::MultVectorXMatrix(double* V, double* M, int d)
{
    d++;
    double* res = new double[d];
    if (!res)
        throw memory_alloc_error();
    for (int i = 0; i < d; i++) {
        double s = 0;
        for (int j = 0; j < d; j++) {
            s += V[j] * M[j * d + i];
        }
        res[i] = s;
    }
    return res;
}
//преобразует единственную точку в точку на экране
QPoint ConcreteConverter1::ConvertSinglePoint(sPoint3d p, double* ConvMatrix)
{
    QPoint res;

    double* pVector = new double[4]; //представление точки в виде вектора
    if (!pVector) { // 4 координаты нужны для использования матрицы переноса
        throw memory_alloc_error();
    }
    pVector[0] = p.x;
    pVector[1] = p.y;
    pVector[2] = p.z;
    pVector[3] = 1;

    //умножаем вектор точки на матрицу преобразований - получаем новую точку в
    //векторном представлении
    double* conversion = MultVectorXMatrix(pVector, ConvMatrix, 3);
    delete pVector;

    if (!conversion) {
        throw memory_alloc_error();
    }

    res.setX((int)floor(conversion[0]));
    res.setY((int)floor(conversion[1]));
    delete conversion;

    return res;
}
