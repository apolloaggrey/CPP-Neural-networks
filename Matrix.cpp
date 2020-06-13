//
// Created by AGGREY APOLLO on 12/21/2019.
//

#include <cassert>
#include <vector>
#include <iostream>
#include <fstream>

class Matrix
{
private:
    std::vector<std::vector<double> > array;
    int height{};
    int width{};
public:

    Matrix()
    = default;

    explicit Matrix(int unit_matrix)
    {
        this->height = unit_matrix;
        this->width = unit_matrix;
        this->array = std::vector<std::vector<double> >(height, std::vector<double>(width));
        int i,j;
        for (i=0 ; i<height ; i++)
        {
            for (j=0 ; j<width ; j++)
            {
                if(i==j)
                {
                    this->array[i][j] = 1;
                }
            }
        }
    }

    Matrix(int height, int width)
    {
        this->height = height;
        this->width = width;
        this->array = std::vector<std::vector<double> >(height, std::vector<double>(width));
    }

    explicit Matrix(std::vector<std::vector<double> > const &array)
    {
        assert(array.size()!=0);
        this->height = array.size();
        this->width = array[0].size();
        this->array = array;
    }


    Matrix(std::string filename)
    {
        std::ifstream file(filename);
        std::string line;
        getline(file, line);
        this->height = std::stoi(line);
        getline(file, line);
        this->width = std::stoi(line);
        this->array = std::vector<std::vector<double> >(height, std::vector<double>(width));
        for (int i = 0; i < height; i++)
        {
            getline(file, line);
            int total=0;
            for (int j = 0; j < width;)
            {
                for(int token=total;token< line.length();token++)
                {
                    if(line[token]==' ')
                    {
                        this->array[i][j] = std::stof(line.substr(total, (token-total)));
                        total = token+1;
                        j++;
                    }
                }
            }
        }
        file.close();
    }


    Matrix add(Matrix const &m) const
    {
        assert(height==m.height && width==m.width);

        Matrix result(height, width);
        int i,j;

        for (i=0 ; i<height ; i++)
        {
            for (j=0 ; j<width ; j++)
            {
                result.array[i][j] = array[i][j] + m.array[i][j];
            }
        }

        return result;
    }

    Matrix operator+(Matrix const &m) const
    {
        assert(height==m.height && width==m.width);

        Matrix result(height, width);
        int i,j;

        for (i=0 ; i<height ; i++)
        {
            for (j=0 ; j<width ; j++)
            {
                result.array[i][j] = array[i][j] + m.array[i][j];
            }
        }

        return result;
    }

    Matrix subtract(Matrix const &m) const
    {
        assert(height==m.height && width==m.width);

        Matrix result(height, width);
        int i,j;

        for (i=0 ; i<height ; i++)
        {
            for (j=0 ; j<width ; j++)
            {
                result.array[i][j] = array[i][j] - m.array[i][j];
            }
        }

        return result;
    }


    Matrix operator-(Matrix const &m) const
    {
        assert(height==m.height && width==m.width);

        Matrix result(height, width);
        int i,j;

        for (i=0 ; i<height ; i++)
        {
            for (j=0 ; j<width ; j++)
            {
                result.array[i][j] = array[i][j] - m.array[i][j];
            }
        }

        return result;
    }
    Matrix  multiply(Matrix const &m) const
    {
        assert(height==m.height && width==m.width);

        Matrix result(height, width);
        int i,j;

        for (i=0 ; i<height ; i++)
        {
            for (j=0 ; j<width ; j++)
            {
                result.array[i][j] = array[i][j] * m.array[i][j];
            }
        }
        return result;
    }

    Matrix multiply(double value)
    {
        Matrix result(height, width);
        int i,j;

        for (i=0 ; i<height ; i++)
        {
            for (j=0 ; j<width ; j++)
            {
                result.array[i][j] = array[i][j] * value;
            }
        }

        return result;
    }

    Matrix operator*(double const &value)
    {
        Matrix result(height, width);
        int i,j;

        for (i=0 ; i<height ; i++)
        {
            for (j=0 ; j<width ; j++)
            {
                result.array[i][j] = array[i][j] * value;
            }
        }

        return result;
    }

    Matrix operator*(Matrix const &m) const
    {
        assert(height==m.height && width==m.width);

        Matrix result(height, width);
        int i,j;

        for (i=0 ; i<height ; i++)
        {
            for (j=0 ; j<width ; j++)
            {
                result.array[i][j] = array[i][j] * m.array[i][j];
            }
        }
        return result;
    }


    Matrix operator^(int x) const
    {
        Matrix result = *this;
        if(x < 0)
        {
            result = result.transpose();
            x *= -1;
        }
        for (int i=1 ; i<x ; i++)
        {
                result = result * *this ;
        }
        return result;
    }

    Matrix dot(Matrix const &m) const
    {
        assert(width==m.height);

        int i,j,h, mwidth = m.width;
        double w=0;

        Matrix result(height, mwidth);

        for (i=0 ; i<height ; i++)
        {
            for (j=0 ; j<mwidth ; j++)
            {
                for (h=0 ; h<width ; h++)
                {
                    w += array[i][h]*m.array[h][j];
                }
                result.array[i][j] = w;
                w=0;
            }
        }

        return result;
    }

    Matrix transpose() const // ij element becomes ji element
    {
        Matrix result(width, height);
        int i,j;

        for (i=0 ; i<width ; i++){
            for (j=0 ; j<height ; j++){
                result.array[i][j] = array[j][i];
            }
        }
        return result;
    }


    Matrix applyFunction(double (*function)(double)) const // takes as parameter a function which prototype looks like : double function(double x)
    {
        Matrix result(height, width);
        int i,j;

        for (i=0 ; i<height ; i++)
        {
            for (j=0 ; j<width ; j++){
                result.array[i][j] = (*function)(array[i][j]);
            }
        }

        return result;
    }

    friend std::ostream& operator<<( std::ostream &flux, const Matrix& M)
    {
        int i,j;
        for (i=0 ; i<M.height ; i++)
        {
            for (j=0 ; j<M.width ; j++)
            {
                flux << M.array[i][j];
                //flux << "";
            }
            //flux << std::endl;
        }
        return flux;
    }

    friend bool operator==(const Matrix& A,const Matrix& B)
    {
        if(A.width==B.width && A.height==B.height)
        {
            int i,j;
            for (i=0 ; i<A.height ; i++)
            {
                for (j=0 ; j<A.width ; j++)
                {
                    if(A.array[i][j] != B.array[i][j] )
                        return false;
                }
            }

        } else return false;
        return true;
    }
    friend bool operator!=(const Matrix& A,const Matrix& B)
    {
        bool not_equal = false;
        if(A.width==B.width && A.height==B.height)
        {
            int i,j;

            for (i=0 ; i<A.height ; i++)
            {
                for (j=0 ; j<A.width ; j++)
                {
                    if(A.array[i][j] != B.array[i][j] )
                        not_equal = true;
                }
            }

        } else return true;
        return not_equal;
    }

    Matrix& operator=(const Matrix& A)
    = default;



    std::string serialize(std::string filename)
    {
//        filename = &R"(F:\Documents\personal\neural_networks\)" [ *filename];
        std::ofstream outfile(filename);
        outfile << this->height<< "\n";
        outfile << this->width<< "\n";
        for (int i = 0; i < this->height; i++)
        {
            for(int j = 0; j < this->width; j++)
            {
                outfile << this->array[i][j] << " ";
            }
            outfile <<"\n";
        }
        outfile.close();
    return filename;
    }

};


