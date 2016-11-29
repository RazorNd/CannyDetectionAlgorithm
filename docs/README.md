# Алгоритм

Алгоритм Кенни включает в себя следующие шаги:

  1. Преобразование изображение в градации серого.
  2. Сглаживание шумов с помощью фильтра Гауса.
  3. Поиск градиентов яркости пикселей с помощью заданого оператора.
  4. Подавление немаксимумов.
  5. Двойная пороговая фильтрация.
  6. Трассировка области неодназначности.
 
Вся реализация алгоритма находится в подпроекте **common** в классе `CannyDetection`:

```C++
class CannyDetection
{
public:
    typedef std::function<PixelsMatrix (const PixelsMatrix &in)> SupressOperatorType;
    CannyDetection();
    CannyDetection(int tMin, int tMax, double sigma);    

    double getSigma() const;
    void setSigma(double value);

    int getTMin() const;
    void setTMin(int value);

    int getTMax() const;
    void setTMax(int value);

    QImage operator() (const QImage &in) const;

    void setSupressOperator(SupressOperatorType &&value);

private:
    double sigma = 1.0;
    int tMin = 45;
    int tMax = 50;
    SupressOperatorType supressOperator = SobelOperator();
};
```

Данный класс содержит методы установки параметров алгоритма, а также `QImage operator() (const QImage &in) const;`, в котором и заключена вся логика алгоритма.
Рассмотрим этот метод подробнее:

```C++
QImage CannyDetection::operator()(const QImage &image) const
{
    PixelsMatrix in = gaussianFilter<5>(PixelsMatrix::fromImage(image), sigma);
    PixelsMatrix nms = supressOperator(in);

    const int nx = in.size.height();
    const int ny = in.size.width();
    const size_t size = static_cast<size_t>(nx * ny);

    std::vector<int> edges(size);
    std::fill(edges.begin(), edges.end(), 0);

    PixelsMatrix out(in.size);
    int c = 1;
    for (int j = 1; j < ny - 1; j++)
        for (int i = 1; i < nx - 1; i++) {
            if (nms[c] >= tMax && out[c] == 0) { // trace edges
                out[c] = PixelsMatrix::MAX_BRIGHTNESS;
                size_t nedges = 1;
                edges[0] = c;

                do {
                    nedges--;
                    const int t = edges[nedges];

                    int nbs[8]; // neighbours
                    nbs[0] = t - nx;     // nn
                    nbs[1] = t + nx;     // ss
                    nbs[2] = t + 1;      // ww
                    nbs[3] = t - 1;      // ee
                    nbs[4] = nbs[0] + 1; // nw
                    nbs[5] = nbs[0] - 1; // ne
                    nbs[6] = nbs[1] + 1; // sw
                    nbs[7] = nbs[1] - 1; // se

                    for (size_t k = 0; k < 8; k++)
                        if (nms[nbs[k]] >= tMin && out[nbs[k]] == 0) {
                            out[nbs[k]] = PixelsMatrix::MAX_BRIGHTNESS;
                            edges[nedges] = nbs[k];
                            nedges++;
                        }
                } while (nedges > 0);
            }
            c++;
        }

    return out.toImage();
}
```

Если сопоставить этот код с шагами алгоритма то:

  1. `PixelsMatrix::fromImage(image)` - преобразование входного изображения во внутрение представление в класс [`PixelsMatrix`](reference/PixelsMatrix.md).
     Данный класс представляет собой матрицу хранящую градацую серого для каждого пикселя.
  2. `gaussianFilter<5>(..., sigma);` - сглаживание шумов с помощью [фильтра Гауса](reference/gaussianFilter.md).
  3. Так как алгоритм подразумевает использование различных опеторов нахождения градиента, то при реализации был использован паттерн *Стратегия*, что позволило
     вынести логику нахождения градиента и подавление немаксимумов в функциональных объектах [`SupressOperatorType`](reference/SupressOperatorType.md):
     ```C++
     PixelsMatrix nms = supressOperator(in);
     ```
  4. Двойная пороговая фильтрация и трассировка области неодназначности выполняется в следующем участке кода:
    ```C++
    for (int j = 1; j < ny - 1; j++)
	  for (int i = 1; i < nx - 1; i++) {
	      if (nms[c] >= tMax && out[c] == 0) { // trace edges
		  out[c] = PixelsMatrix::MAX_BRIGHTNESS;
		  size_t nedges = 1;
		  edges[0] = c;

		  do {
		      nedges--;
		      const int t = edges[nedges];

		      int nbs[8]; // neighbours
		      nbs[0] = t - nx;     // nn
		      nbs[1] = t + nx;     // ss
		      nbs[2] = t + 1;      // ww
		      nbs[3] = t - 1;      // ee
		      nbs[4] = nbs[0] + 1; // nw
		      nbs[5] = nbs[0] - 1; // ne
		      nbs[6] = nbs[1] + 1; // sw
		      nbs[7] = nbs[1] - 1; // se

		      for (size_t k = 0; k < 8; k++)
			  if (nms[nbs[k]] >= tMin && out[nbs[k]] == 0) {
			      out[nbs[k]] = PixelsMatrix::MAX_BRIGHTNESS;
			      edges[nedges] = nbs[k];
			      nedges++;
			  }
		  } while (nedges > 0);
	      }
	      c++;
	  }
    ```
    где для всех пикселей, которые проходят, через верхний порог фильтрации выполняется [трассировка](algorithm/trace_edges.md) соседних пикселей и если они проходят через нижний порог фильрации, то помечаются, как прощедщие и трасировка продолжается и для соседних пикселей.   




