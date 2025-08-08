#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/iio/iio.h>


struct adi_ad5592r_s_st {
    bool enable;
    int chan0;
    int chan1;
};

static int adi_ad5592r_s_read_raw(struct iio_dev *indio_dev,
                struct iio_chan_spec const *chan,
                int *val,
                int *val2,
                long mask
)
{
    struct adi_ad5592r_s_st *st = iio_priv(indio_dev);
        switch (mask) {
            case IIO_CHAN_INFO_ENABLE:
                *val = st->enable;
                return IIO_VAL_INT;
            case IIO_CHAN_INFO_RAW:
                if (chan->channel)
                    *val = st->chan0;
                else
                    *val = st->chan1;
            return IIO_VAL_INT;
}
    return -EINVAL;
}

static int adi_ad5592r_s_write_raw(struct iio_dev *indio_dev,
                struct iio_chan_spec const *chan,
                int val,
                int val2,
                long mask
)
{
    struct adi_ad5592r_s_st *st = iio_priv(indio_dev);
        switch (mask) {
            case IIO_CHAN_INFO_ENABLE:
                st->enable = val;
                return 0;
            case IIO_CHAN_INFO_RAW:
                if (chan->channel)
                    st->chan1 = val;
                else
                    st->chan0 = val;
            return 0;
}
        return -EINVAL;
}
static const struct iio_info adi_ad5592r_s_info = {
    .read_raw = &adi_ad5592r_s_read_raw,
    .write_raw = &adi_ad5592r_s_write_raw,
};

static const struct iio_chan_spec adi_ad5592r_s_channels[] = {
    {
        .type = IIO_VOLTAGE,
        .channel = 0,
        .info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
        .info_mask_shared_by_all = BIT(IIO_CHAN_INFO_ENABLE),
        .output = 0,
        .indexed = 1,
}, {
        .type = IIO_VOLTAGE,
        .channel = 1,
        .info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
        .info_mask_shared_by_all = BIT(IIO_CHAN_INFO_ENABLE),
        .output = 0,
        .indexed = 1,
},
};
static int adi_ad5592r_s_probe(struct spi_device *spi)
{
    struct iio_dev *indio_dev;
    struct adi_ad5592r_s_st *st;
    indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
    if (!indio_dev)
        return -ENOMEM;
    st = iio_priv(indio_dev);
        st->enable = 0;
        st->chan0 = 0;
        st->chan1 = 0;
        indio_dev->name = "ad5592r_s";
        indio_dev->info = &adi_ad5592r_s_info;
        indio_dev->channels = adi_ad5592r_s_channels;
        indio_dev->num_channels = ARRAY_SIZE(adi_ad5592r_s_channels);
        indio_dev->modes = INDIO_DIRECT_MODE;
        return devm_iio_device_register(&spi->dev, indio_dev);
}

/*test*/
static struct spi_driver adi_ad5592r_s_driver = {
    .driver = {
        .name = "ad5592r_s",
    },
    .probe = adi_ad5592r_s_probe,

};
module_spi_driver(adi_ad5592r_s_driver);


MODULE_AUTHOR("Dragos Bogdan <dragos.bogdan@analog.com>");
MODULE_DESCRIPTION("IIO ADI Emulator Driver");
MODULE_LICENSE("GPL v2");