# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

class TestDayTimeIntervalArray < Test::Unit::TestCase
  include Helper::Buildable
  include Helper::Omittable

  def test_new
    zero_day_millisecond = Arrow::DayMillisecond.new(0, 0)
    first_day_millisecond = Arrow::DayMillisecond.new(1, 100)
    second_day_millisecond = Arrow::DayMillisecond.new(3, 100)
    raw_data = [zero_day_millisecond, first_day_millisecond, second_day_millisecond]
    array = build_day_time_interval_array(raw_data)
    assert_equal(array.get_value(1).day, first_day_millisecond.day)
  end

  def test_value
    day_millisecond = Arrow::DayMillisecond.new(3, 100)

    builder = Arrow::DayTimeIntervalArrayBuilder.new
    builder.append_value(day_millisecond)
    array = builder.finish
    assert_equal(day_millisecond.day, array.get_value(0).day)
  end

  def test_values
    first_day_millisecond = Arrow::DayMillisecond.new(1, 100)
    second_day_millisecond = Arrow::DayMillisecond.new(3, 100)

    builder = Arrow::DayTimeIntervalArrayBuilder.new
    builder.append_value(first_day_millisecond)
    builder.append_value(second_day_millisecond)
    array = builder.finish
    assert_equal([first_day_millisecond, second_day_millisecond], array.values)
  end  
end
