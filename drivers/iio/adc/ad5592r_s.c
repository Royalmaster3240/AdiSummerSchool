#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/iio/iio.h>


static const struct iio_info adi_ad5592r_s_info = {
};


static int adi_ad5592r_s_probe(struct spi_device *spi)
{
    struct iio_dev *indio_dev;
    indio_dev = devm_iio_device_alloc(&spi->dev, 0);
    if (!indio_dev)
        return -ENOMEM;
    indio_dev->name = "iio-adi-ad5592r_s";
    indio_dev->info = &adi_ad5592r_s_info;
    return devm_iio_device_register(&spi->dev, indio_dev);
}


static struct spi_driver adi_ad5592r_s_driver = {
    .driver = {
        .name = "iio-adi-ad5592r_s",
    },
    .probe = adi_ad5592r_s_probe,

};
module_spi_driver(adi_ad5592r_s_driver);


MODULE_AUTHOR("Dragos Bogdan <dragos.bogdan@analog.com>");
MODULE_DESCRIPTION("IIO ADI Emulator Driver");
MODULE_LICENSE("GPL v2");