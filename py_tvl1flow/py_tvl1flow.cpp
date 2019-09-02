// =============================================================================
// TVL1Flowのpythonラッパー
// =============================================================================
#define PY_ARRAY_UNIQUE_SYMBOL pbcvt_ARRAY_API
#include <opencv2/core.hpp>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include "tvl1flow.hpp"
#include "flow2image.hpp"
#include "pyboostcvconverter/pyboostcvconverter.hpp"
namespace py = boost::python;

class PyTVL1Flow {
public:
    PyTVL1Flow() = default;

    PyObject* calc(PyObject* src0, PyObject* src1) {
        // cv::Matに変換
        cv::Mat frame0, frame1;
        frame0 = pbcvt::fromNDArrayToMat(src0);
        frame1 = pbcvt::fromNDArrayToMat(src1);
        // Broxflow計算
        auto flowout = flow.calc(frame0, frame1);

        // 画像に変換
        cv::Mat flowimg;
        ss::flow2image(flowout, flowimg);

        // 出力
        PyObject* ret =  pbcvt::fromMatToNDArray(flowimg);
        return ret;
    }

    /**
     * 2CH画像に変換
     * @param  src0 画像1枚目
     * @param  src1 画像2枚目
     * @return      出力
     */
    PyObject* calc2CH(PyObject* src0, PyObject* src1, double bound=20.0) {
        // cv::Matに変換
        cv::Mat frame0, frame1;
        frame0 = pbcvt::fromNDArrayToMat(src0);
        frame1 = pbcvt::fromNDArrayToMat(src1);
        // オプティカルフロー計算
        auto flowout = flow.calc(frame0, frame1);

        // 画像に変換
        cv::Mat flowimg;
        ss::flow2image2CH(flowout, flowimg, bound);

        // 出力
        PyObject* ret =  pbcvt::fromMatToNDArray(flowimg);
        return ret;
    }
private:
    ss::TVL1Flow flow;
};

#if (PY_VERSION_HEX >= 0x03000000)
    static void *init_ar() {
#else
    static void init_ar() {
#endif
    Py_Initialize();

    import_array();
    return NUMPY_IMPORT_ARRAY_RETVAL;
}

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(tvl1flow_calc2ch_overloads, PyTVL1Flow::calc2CH, 2, 3)

BOOST_PYTHON_MODULE(py_tvl1flow)
{
    using namespace ss;
    init_ar();

    auto tinfo = py::type_id<cv::Mat>();
    auto reg = py::converter::registry::query(tinfo);
    if(reg == nullptr) {
        py::to_python_converter<cv::Mat, pbcvt::matToNDArrayBoostConverter>();
    } else if ((*reg).m_to_python == nullptr) {
        py::to_python_converter<cv::Mat, pbcvt::matToNDArrayBoostConverter>();
    }
    pbcvt::matFromNDArrayBoostConverter();

    py::def("setDevice", &TVL1Flow::setDevice);
    py::def("resetDevice", &TVL1Flow::resetDevice);

    py::class_<PyTVL1Flow>("TVL1Flow")
        .def(py::init<>())
        .def("calc2CH",  &PyTVL1Flow::calc2CH, tvl1flow_calc2ch_overloads())
        .def("calc", &PyTVL1Flow::calc)
        ;
}
