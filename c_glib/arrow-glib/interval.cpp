/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <memory>
#include <arrow-glib/interval.hpp>
#include <arrow/type.h>

G_BEGIN_DECLS

/**
 * SECTION: interval
 * @section_id: interval
 * @title: day milliseconds and month day nanoseconds interval classes
 * @include: arrow-glib/arrow-glib.h
 *
 * #GArrowDayMillisecond is a day milliseconds value class.
 *
 * #GArrowMonthDayNano is a month day nanoseconds value class.
 *
 * Since: 8.0.0
 */

typedef struct GArrowDayMillisecondPrivate_ {
  arrow::DayTimeIntervalType::DayMilliseconds day_millisecond;
} GArrowDayMillisecondPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GArrowDayMillisecond,
                           garrow_day_millisecond,
                           G_TYPE_OBJECT)

#define GARROW_DAY_MILLISECOND_GET_PRIVATE(object)  \
  static_cast<GArrowDayMillisecondPrivate *>(       \
    garrow_day_millisecond_get_instance_private(    \
      GARROW_DAY_MILLISECOND(object)))

enum {
  PROP_DAY_MILLISECOND_DAY = 1,
  PROP_DAY_MILLISECOND_MILLISECOND,
};

static void
garrow_day_millisecond_set_property(GObject *object,
                                     guint prop_id,
                                     const GValue *value,
                                     GParamSpec *pspec)
{
  auto priv = GARROW_DAY_MILLISECOND_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_DAY_MILLISECOND_DAY:
    priv->day_millisecond.days = g_value_get_int(value);
    break;
  case PROP_DAY_MILLISECOND_MILLISECOND:
    priv->day_millisecond.milliseconds = g_value_get_int(value);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
garrow_day_millisecond_get_property(GObject *object,
                                    guint prop_id,
                                    GValue *value,
                                    GParamSpec *pspec)
{
  auto priv = GARROW_DAY_MILLISECOND_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_DAY_MILLISECOND_DAY:
    g_value_set_int(value, priv->day_millisecond.days);
    break;
  case PROP_DAY_MILLISECOND_MILLISECOND:
    g_value_set_int(value, priv->day_millisecond.milliseconds);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
garrow_day_millisecond_init(GArrowDayMillisecond *object)
{
  auto priv = GARROW_DAY_MILLISECOND_GET_PRIVATE(object);
  priv->day_millisecond = arrow::DayTimeIntervalType::DayMilliseconds();
}

static void
garrow_day_millisecond_class_init(GArrowDayMillisecondClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->set_property = garrow_day_millisecond_set_property;
  gobject_class->get_property = garrow_day_millisecond_get_property;

  arrow::DayTimeIntervalType::DayMilliseconds day_millisecond;
  /**
   * GArrowDayMillisecond:day:
   *
   * #GArrowDayMillisecond day value
   *
   * Since: 8.0.0
   */
  spec = g_param_spec_int("day",
                            "Day",
                            "GArrowDayMillisecond day value",
                            G_MININT32,
                            G_MAXINT32,
                            day_millisecond.days,
                            static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class,
                                  PROP_DAY_MILLISECOND_DAY,
                                  spec);

  /**
   * GArrowDayMillisecond:millisecond:
   *
   * #GArrowDayMillisecond millisecond value
   *
   * Since: 8.0.0
   */
  spec = g_param_spec_int("millisecond",
                            "Millisecond",
                            "GArrowDayMillisecond millisecond value",
                            G_MININT32,
                            G_MAXINT32,
                            day_millisecond.milliseconds,
                            static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class,
                                  PROP_DAY_MILLISECOND_MILLISECOND,
                                  spec);
}

/**
 * garrow_day_millisecond_new:
 * @days: day
 * @milliseconds: milliseconds
 *
 * Returns: (nullable):
 *   A newly created #GArrowDayMillisecond.
 *
 * Since: 8.0.0
 */
GArrowDayMillisecond *
garrow_day_millisecond_new(gint32 days, gint32 milliseconds)
{
  arrow::DayTimeIntervalType::DayMilliseconds arrow_day_millisecond(days, milliseconds);
  return garrow_day_millisecond_new_raw(&arrow_day_millisecond);
}

/**
 * garrow_day_millisecond_equal:
 * @day_millisecond: A #GArrowDayMillisecond.
 * @other_day_millisecond: A #GArrowDayMillisecond to be compared.
 *
 * Returns: %TRUE if both of them have the same data, %FALSE
 *   otherwise.
 *
 * Since: 8.0.0
 */
gboolean
garrow_day_millisecond_equal(GArrowDayMillisecond *day_millisecond, GArrowDayMillisecond *other_day_millisecond)
{
  auto priv = GARROW_DAY_MILLISECOND_GET_PRIVATE(day_millisecond);
  auto other_priv = GARROW_DAY_MILLISECOND_GET_PRIVATE(other_day_millisecond);

  return priv->day_millisecond == other_priv->day_millisecond;
}

/**
 * garrow_day_millisecond_less_than:
 * @day_millisecond: A #GArrowDayMillisecond.
 * @other_day_millisecond: A #GArrowDayMillisecond to be compared.
 *
 * Returns: %TRUE if the value is less than the other value,
 *   %FALSE otherwise.
 *
 * Since: 8.0.0
 */
gboolean
garrow_day_millisecond_less_than(GArrowDayMillisecond *day_millisecond, GArrowDayMillisecond *other_day_millisecond)
{
  auto priv = GARROW_DAY_MILLISECOND_GET_PRIVATE(day_millisecond);
  auto other_priv = GARROW_DAY_MILLISECOND_GET_PRIVATE(other_day_millisecond);

  return priv->day_millisecond < other_priv->day_millisecond;
}


typedef struct GArrowMonthDayNanoPrivate_ {
  arrow::MonthDayNanoIntervalType::MonthDayNanos month_day_nano;
} GArrowMonthDayNanoPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GArrowMonthDayNano,
                           garrow_month_day_nano,
                           G_TYPE_OBJECT)

#define GARROW_MONTH_DAY_NANO_GET_PRIVATE(object)  \
  static_cast<GArrowMonthDayNanoPrivate *>(       \
    garrow_month_day_nano_get_instance_private(    \
      GARROW_MONTH_DAY_NANO(object)))

enum {
  PROP_MONTH_DAY_NANO_MONTH = 1,
  PROP_MONTH_DAY_NANO_DAY,
  PROP_MONTH_DAY_NANO_NANOSECOND,
};

static void
garrow_month_day_nano_set_property(GObject *object,
                                     guint prop_id,
                                     const GValue *value,
                                     GParamSpec *pspec)
{
  auto priv = GARROW_MONTH_DAY_NANO_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_MONTH_DAY_NANO_MONTH:
    priv->month_day_nano.months = g_value_get_int(value);
    break;
  case PROP_MONTH_DAY_NANO_DAY:
    priv->month_day_nano.days = g_value_get_int(value);
    break;
  case PROP_MONTH_DAY_NANO_NANOSECOND:
    priv->month_day_nano.nanoseconds = g_value_get_int64(value);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
garrow_month_day_nano_get_property(GObject *object,
                                    guint prop_id,
                                    GValue *value,
                                    GParamSpec *pspec)
{
  auto priv = GARROW_MONTH_DAY_NANO_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_MONTH_DAY_NANO_MONTH:
    g_value_set_int(value, priv->month_day_nano.months);
    break;
  case PROP_MONTH_DAY_NANO_DAY:
    g_value_set_int(value, priv->month_day_nano.days);
    break;
  case PROP_MONTH_DAY_NANO_NANOSECOND:
    g_value_set_int64(value, priv->month_day_nano.nanoseconds);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
garrow_month_day_nano_init(GArrowMonthDayNano *object)
{
  auto priv = GARROW_MONTH_DAY_NANO_GET_PRIVATE(object);
  priv->month_day_nano = arrow::MonthDayNanoIntervalType::MonthDayNanos();
}

static void
garrow_month_day_nano_class_init(GArrowMonthDayNanoClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->set_property = garrow_month_day_nano_set_property;
  gobject_class->get_property = garrow_month_day_nano_get_property;

  arrow::MonthDayNanoIntervalType::MonthDayNanos month_day_nano;
  /**
   * GArrowMonthDayNano:month:
   *
   * #GArrowMonthDayNano month value
   *
   * Since: 8.0.0
   */
  spec = g_param_spec_int("month",
                            "Month",
                            "GArrowMonthDayNano month value",
                            G_MININT32,
                            G_MAXINT32,
                            month_day_nano.months,
                            static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class,
                                  PROP_MONTH_DAY_NANO_MONTH,
                                  spec);

  /**
   * GArrowMonthDayNano:day:
   *
   * #GArrowMonthDayNano day value
   *
   * Since: 8.0.0
   */
  spec = g_param_spec_int("day",
                            "Day",
                            "GArrowMonthDayNano day value",
                            G_MININT32,
                            G_MAXINT32,
                            month_day_nano.days,
                            static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class,
                                  PROP_MONTH_DAY_NANO_DAY,
                                  spec);

  /**
   * GArrowMonthDayNano:nanosecond:
   *
   * #GArrowMonthDayNano nanosecond value
   *
   * Since: 8.0.0
   */
  spec = g_param_spec_int64("nanosecond",
                            "nanosecond",
                            "GArrowMonthDayNano nanosecond value",
                            G_MININT64,
                            G_MAXINT64,
                            month_day_nano.nanoseconds,
                            static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class,
                                  PROP_MONTH_DAY_NANO_NANOSECOND,
                                  spec);
}

/**
 * garrow_month_day_nano_new:
 * @months: months
 * @days: days
 * @nanoseconds: nanoseconds
 *
 * Returns: (nullable):
 *   A newly created #GArrowMonthDayNano.
 *
 * Since: 8.0.0
 */
GArrowMonthDayNano *
garrow_month_day_nano_new(gint32 months, gint32 days, gint64 nanoseconds)
{
  arrow::MonthDayNanoIntervalType::MonthDayNanos arrow_month_day_nano;
  arrow_month_day_nano.months = months;
  arrow_month_day_nano.days = days;
  arrow_month_day_nano.nanoseconds = nanoseconds;
  return garrow_month_day_nano_new_raw(&arrow_month_day_nano);
}

/**
 * garrow_month_day_nano_equal:
 * @month_nano_day: A #GArrowMonthDayNano.
 * @other_month_nano_day: A #GArrowMonthDayNano to be compared.
 *
 * Returns: %TRUE if both of them have the same data, %FALSE
 *   otherwise.
 *
 * Since: 8.0.0
 */
gboolean
garrow_month_day_nano_equal(GArrowMonthDayNano *month_nano_day, GArrowMonthDayNano *other_month_nano_day)
{
  auto priv = GARROW_MONTH_DAY_NANO_GET_PRIVATE(month_nano_day);
  auto other_priv = GARROW_MONTH_DAY_NANO_GET_PRIVATE(other_month_nano_day);

  return priv->month_day_nano == other_priv->month_day_nano;
}


G_END_DECLS

GArrowDayMillisecond *
garrow_day_millisecond_new_raw(arrow::DayTimeIntervalType::DayMilliseconds *arrow_day_millisecond)
{
  auto day_millisecond = g_object_new(garrow_day_millisecond_get_type(),
                                 "day", arrow_day_millisecond->days,
                                 "millisecond", arrow_day_millisecond->milliseconds,
                                 NULL);
  return GARROW_DAY_MILLISECOND(day_millisecond);
}

arrow::DayTimeIntervalType::DayMilliseconds *
garrow_day_millisecond_get_raw(GArrowDayMillisecond *day_millisecond)
{
  auto priv = GARROW_DAY_MILLISECOND_GET_PRIVATE(day_millisecond);
  return &priv->day_millisecond;
}

const arrow::DayTimeIntervalType::DayMilliseconds *
garrow_day_millisecond_get_raw(const GArrowDayMillisecond *day_millisecond)
{
  auto priv = GARROW_DAY_MILLISECOND_GET_PRIVATE(const_cast<GArrowDayMillisecond *>(day_millisecond));
  return &priv->day_millisecond;
}


GArrowMonthDayNano *
garrow_month_day_nano_new_raw(arrow::MonthDayNanoIntervalType::MonthDayNanos *arrow_month_day_nano)
{
  auto month_day_nano = g_object_new(garrow_month_day_nano_get_type(),
                                 "month", arrow_month_day_nano->months,
                                 "day", arrow_month_day_nano->days,
                                 "nanosecond", arrow_month_day_nano->nanoseconds,
                                 NULL);
  return GARROW_MONTH_DAY_NANO(month_day_nano);
}

arrow::MonthDayNanoIntervalType::MonthDayNanos *
garrow_month_day_nano_get_raw(GArrowMonthDayNano *month_day_nano)
{
  auto priv = GARROW_MONTH_DAY_NANO_GET_PRIVATE(month_day_nano);
  return &priv->month_day_nano;
}

const arrow::MonthDayNanoIntervalType::MonthDayNanos *
garrow_month_day_nano_get_raw(const GArrowMonthDayNano *month_day_nano)
{
  auto priv = GARROW_MONTH_DAY_NANO_GET_PRIVATE(const_cast<GArrowMonthDayNano *>(month_day_nano));
  return &priv->month_day_nano;
}
