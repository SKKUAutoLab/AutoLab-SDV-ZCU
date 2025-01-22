// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file ImagePubSubTypes.cpp
 * This header file contains the implementation of the serialization functions.
 *
 * This file was generated by the tool fastddsgen.
 */


#include <fastdds/rtps/common/CdrSerialization.hpp>

#include "ImagePubSubTypes.h"
#include "ImageCdrAux.hpp"

using SerializedPayload_t = eprosima::fastrtps::rtps::SerializedPayload_t;
using InstanceHandle_t = eprosima::fastrtps::rtps::InstanceHandle_t;
using DataRepresentationId_t = eprosima::fastdds::dds::DataRepresentationId_t;

namespace builtin_interfaces {
    namespace msg {
        namespace dds_ {


            Time_PubSubType::Time_PubSubType()
            {
                setName("builtin_interfaces::msg::dds_::Time_");
                uint32_t type_size =
            #if FASTCDR_VERSION_MAJOR == 1
                    static_cast<uint32_t>(Time_::getMaxCdrSerializedSize());
            #else
                    builtin_interfaces_msg_dds__Time__max_cdr_typesize;
            #endif
                type_size += static_cast<uint32_t>(eprosima::fastcdr::Cdr::alignment(type_size, 4)); /* possible submessage alignment */
                m_typeSize = type_size + 4; /*encapsulation*/
                m_isGetKeyDefined = false;
                uint32_t keyLength = builtin_interfaces_msg_dds__Time__max_key_cdr_typesize > 16 ? builtin_interfaces_msg_dds__Time__max_key_cdr_typesize : 16;
                m_keyBuffer = reinterpret_cast<unsigned char*>(malloc(keyLength));
                memset(m_keyBuffer, 0, keyLength);
            }

            Time_PubSubType::~Time_PubSubType()
            {
                if (m_keyBuffer != nullptr)
                {
                    free(m_keyBuffer);
                }
            }

            bool Time_PubSubType::serialize(
                    void* data,
                    SerializedPayload_t* payload,
                    DataRepresentationId_t data_representation)
            {
                Time_* p_type = static_cast<Time_*>(data);

                // Object that manages the raw buffer.
                eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->max_size);
                // Object that serializes the data.
                eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
                        data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
                        eprosima::fastcdr::CdrVersion::XCDRv1 : eprosima::fastcdr::CdrVersion::XCDRv2);
                payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
            #if FASTCDR_VERSION_MAJOR > 1
                ser.set_encoding_flag(
                    data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
                    eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR  :
                    eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2);
            #endif // FASTCDR_VERSION_MAJOR > 1

                try
                {
                    // Serialize encapsulation
                    ser.serialize_encapsulation();
                    // Serialize the object.
                    ser << *p_type;
            #if FASTCDR_VERSION_MAJOR > 1
                    ser.set_dds_cdr_options({0,0});
            #else
                    ser.setDDSCdrOptions(0);
            #endif // FASTCDR_VERSION_MAJOR > 1
                }
                catch (eprosima::fastcdr::exception::Exception& /*exception*/)
                {
                    return false;
                }

                // Get the serialized length
            #if FASTCDR_VERSION_MAJOR == 1
                payload->length = static_cast<uint32_t>(ser.getSerializedDataLength());
            #else
                payload->length = static_cast<uint32_t>(ser.get_serialized_data_length());
            #endif // FASTCDR_VERSION_MAJOR == 1
                return true;
            }

            bool Time_PubSubType::deserialize(
                    SerializedPayload_t* payload,
                    void* data)
            {
                try
                {
                    // Convert DATA to pointer of your type
                    Time_* p_type = static_cast<Time_*>(data);

                    // Object that manages the raw buffer.
                    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->length);

                    // Object that deserializes the data.
                    eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN
            #if FASTCDR_VERSION_MAJOR == 1
                            , eprosima::fastcdr::Cdr::CdrType::DDS_CDR
            #endif // FASTCDR_VERSION_MAJOR == 1
                            );

                    // Deserialize encapsulation.
                    deser.read_encapsulation();
                    payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

                    // Deserialize the object.
                    deser >> *p_type;
                }
                catch (eprosima::fastcdr::exception::Exception& /*exception*/)
                {
                    return false;
                }

                return true;
            }

            std::function<uint32_t()> Time_PubSubType::getSerializedSizeProvider(
                    void* data,
                    DataRepresentationId_t data_representation)
            {
                return [data, data_representation]() -> uint32_t
                       {
            #if FASTCDR_VERSION_MAJOR == 1
                           static_cast<void>(data_representation);
                           return static_cast<uint32_t>(type::getCdrSerializedSize(*static_cast<Time_*>(data))) +
                                  4u /*encapsulation*/;
            #else
                           try
                           {
                               eprosima::fastcdr::CdrSizeCalculator calculator(
                                   data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
                                   eprosima::fastcdr::CdrVersion::XCDRv1 :eprosima::fastcdr::CdrVersion::XCDRv2);
                               size_t current_alignment {0};
                               return static_cast<uint32_t>(calculator.calculate_serialized_size(
                                           *static_cast<Time_*>(data), current_alignment)) +
                                       4u /*encapsulation*/;
                           }
                           catch (eprosima::fastcdr::exception::Exception& /*exception*/)
                           {
                               return 0;
                           }
            #endif // FASTCDR_VERSION_MAJOR == 1
                       };
            }

            void* Time_PubSubType::createData()
            {
                return reinterpret_cast<void*>(new Time_());
            }

            void Time_PubSubType::deleteData(
                    void* data)
            {
                delete(reinterpret_cast<Time_*>(data));
            }

            bool Time_PubSubType::getKey(
                    void* data,
                    InstanceHandle_t* handle,
                    bool force_md5)
            {
                if (!m_isGetKeyDefined)
                {
                    return false;
                }

                Time_* p_type = static_cast<Time_*>(data);

                // Object that manages the raw buffer.
                eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(m_keyBuffer),
                        builtin_interfaces_msg_dds__Time__max_key_cdr_typesize);

                // Object that serializes the data.
                eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS, eprosima::fastcdr::CdrVersion::XCDRv1);
            #if FASTCDR_VERSION_MAJOR == 1
                p_type->serializeKey(ser);
            #else
                eprosima::fastcdr::serialize_key(ser, *p_type);
            #endif // FASTCDR_VERSION_MAJOR == 1
                if (force_md5 || builtin_interfaces_msg_dds__Time__max_key_cdr_typesize > 16)
                {
                    m_md5.init();
            #if FASTCDR_VERSION_MAJOR == 1
                    m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.getSerializedDataLength()));
            #else
                    m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.get_serialized_data_length()));
            #endif // FASTCDR_VERSION_MAJOR == 1
                    m_md5.finalize();
                    for (uint8_t i = 0; i < 16; ++i)
                    {
                        handle->value[i] = m_md5.digest[i];
                    }
                }
                else
                {
                    for (uint8_t i = 0; i < 16; ++i)
                    {
                        handle->value[i] = m_keyBuffer[i];
                    }
                }
                return true;
            }


        } //End of namespace dds_


    } //End of namespace msg


} //End of namespace builtin_interfaces

namespace std_msgs {
    namespace msg {
        namespace dds_ {


            Header_PubSubType::Header_PubSubType()
            {
                setName("std_msgs::msg::dds_::Header_");
                uint32_t type_size =
            #if FASTCDR_VERSION_MAJOR == 1
                    static_cast<uint32_t>(Header_::getMaxCdrSerializedSize());
            #else
                    std_msgs_msg_dds__Header__max_cdr_typesize;
            #endif
                type_size += static_cast<uint32_t>(eprosima::fastcdr::Cdr::alignment(type_size, 4)); /* possible submessage alignment */
                m_typeSize = type_size + 4; /*encapsulation*/
                m_isGetKeyDefined = false;
                uint32_t keyLength = std_msgs_msg_dds__Header__max_key_cdr_typesize > 16 ? std_msgs_msg_dds__Header__max_key_cdr_typesize : 16;
                m_keyBuffer = reinterpret_cast<unsigned char*>(malloc(keyLength));
                memset(m_keyBuffer, 0, keyLength);
            }

            Header_PubSubType::~Header_PubSubType()
            {
                if (m_keyBuffer != nullptr)
                {
                    free(m_keyBuffer);
                }
            }

            bool Header_PubSubType::serialize(
                    void* data,
                    SerializedPayload_t* payload,
                    DataRepresentationId_t data_representation)
            {
                Header_* p_type = static_cast<Header_*>(data);

                // Object that manages the raw buffer.
                eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->max_size);
                // Object that serializes the data.
                eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
                        data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
                        eprosima::fastcdr::CdrVersion::XCDRv1 : eprosima::fastcdr::CdrVersion::XCDRv2);
                payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
            #if FASTCDR_VERSION_MAJOR > 1
                ser.set_encoding_flag(
                    data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
                    eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR  :
                    eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2);
            #endif // FASTCDR_VERSION_MAJOR > 1

                try
                {
                    // Serialize encapsulation
                    ser.serialize_encapsulation();
                    // Serialize the object.
                    ser << *p_type;
            #if FASTCDR_VERSION_MAJOR > 1
                    ser.set_dds_cdr_options({0,0});
            #else
                    ser.setDDSCdrOptions(0);
            #endif // FASTCDR_VERSION_MAJOR > 1
                }
                catch (eprosima::fastcdr::exception::Exception& /*exception*/)
                {
                    return false;
                }

                // Get the serialized length
            #if FASTCDR_VERSION_MAJOR == 1
                payload->length = static_cast<uint32_t>(ser.getSerializedDataLength());
            #else
                payload->length = static_cast<uint32_t>(ser.get_serialized_data_length());
            #endif // FASTCDR_VERSION_MAJOR == 1
                return true;
            }

            bool Header_PubSubType::deserialize(
                    SerializedPayload_t* payload,
                    void* data)
            {
                try
                {
                    // Convert DATA to pointer of your type
                    Header_* p_type = static_cast<Header_*>(data);

                    // Object that manages the raw buffer.
                    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->length);

                    // Object that deserializes the data.
                    eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN
            #if FASTCDR_VERSION_MAJOR == 1
                            , eprosima::fastcdr::Cdr::CdrType::DDS_CDR
            #endif // FASTCDR_VERSION_MAJOR == 1
                            );

                    // Deserialize encapsulation.
                    deser.read_encapsulation();
                    payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

                    // Deserialize the object.
                    deser >> *p_type;
                }
                catch (eprosima::fastcdr::exception::Exception& /*exception*/)
                {
                    return false;
                }

                return true;
            }

            std::function<uint32_t()> Header_PubSubType::getSerializedSizeProvider(
                    void* data,
                    DataRepresentationId_t data_representation)
            {
                return [data, data_representation]() -> uint32_t
                       {
            #if FASTCDR_VERSION_MAJOR == 1
                           static_cast<void>(data_representation);
                           return static_cast<uint32_t>(type::getCdrSerializedSize(*static_cast<Header_*>(data))) +
                                  4u /*encapsulation*/;
            #else
                           try
                           {
                               eprosima::fastcdr::CdrSizeCalculator calculator(
                                   data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
                                   eprosima::fastcdr::CdrVersion::XCDRv1 :eprosima::fastcdr::CdrVersion::XCDRv2);
                               size_t current_alignment {0};
                               return static_cast<uint32_t>(calculator.calculate_serialized_size(
                                           *static_cast<Header_*>(data), current_alignment)) +
                                       4u /*encapsulation*/;
                           }
                           catch (eprosima::fastcdr::exception::Exception& /*exception*/)
                           {
                               return 0;
                           }
            #endif // FASTCDR_VERSION_MAJOR == 1
                       };
            }

            void* Header_PubSubType::createData()
            {
                return reinterpret_cast<void*>(new Header_());
            }

            void Header_PubSubType::deleteData(
                    void* data)
            {
                delete(reinterpret_cast<Header_*>(data));
            }

            bool Header_PubSubType::getKey(
                    void* data,
                    InstanceHandle_t* handle,
                    bool force_md5)
            {
                if (!m_isGetKeyDefined)
                {
                    return false;
                }

                Header_* p_type = static_cast<Header_*>(data);

                // Object that manages the raw buffer.
                eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(m_keyBuffer),
                        std_msgs_msg_dds__Header__max_key_cdr_typesize);

                // Object that serializes the data.
                eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS, eprosima::fastcdr::CdrVersion::XCDRv1);
            #if FASTCDR_VERSION_MAJOR == 1
                p_type->serializeKey(ser);
            #else
                eprosima::fastcdr::serialize_key(ser, *p_type);
            #endif // FASTCDR_VERSION_MAJOR == 1
                if (force_md5 || std_msgs_msg_dds__Header__max_key_cdr_typesize > 16)
                {
                    m_md5.init();
            #if FASTCDR_VERSION_MAJOR == 1
                    m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.getSerializedDataLength()));
            #else
                    m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.get_serialized_data_length()));
            #endif // FASTCDR_VERSION_MAJOR == 1
                    m_md5.finalize();
                    for (uint8_t i = 0; i < 16; ++i)
                    {
                        handle->value[i] = m_md5.digest[i];
                    }
                }
                else
                {
                    for (uint8_t i = 0; i < 16; ++i)
                    {
                        handle->value[i] = m_keyBuffer[i];
                    }
                }
                return true;
            }


        } //End of namespace dds_


    } //End of namespace msg


} //End of namespace std_msgs

namespace sensor_msgs {
    namespace msg {
        namespace dds_ {




            Image_PubSubType::Image_PubSubType()
            {
                setName("sensor_msgs::msg::dds_::Image_");
                uint32_t type_size =
            #if FASTCDR_VERSION_MAJOR == 1
                    static_cast<uint32_t>(Image_::getMaxCdrSerializedSize());
            #else
                    sensor_msgs_msg_dds__Image__max_cdr_typesize;
            #endif
                type_size += static_cast<uint32_t>(eprosima::fastcdr::Cdr::alignment(type_size, 4)); /* possible submessage alignment */
                m_typeSize = type_size + 4; /*encapsulation*/
                m_isGetKeyDefined = false;
                uint32_t keyLength = sensor_msgs_msg_dds__Image__max_key_cdr_typesize > 16 ? sensor_msgs_msg_dds__Image__max_key_cdr_typesize : 16;
                m_keyBuffer = reinterpret_cast<unsigned char*>(malloc(keyLength));
                memset(m_keyBuffer, 0, keyLength);
            }

            Image_PubSubType::~Image_PubSubType()
            {
                if (m_keyBuffer != nullptr)
                {
                    free(m_keyBuffer);
                }
            }

            bool Image_PubSubType::serialize(
                    void* data,
                    SerializedPayload_t* payload,
                    DataRepresentationId_t data_representation)
            {
                Image_* p_type = static_cast<Image_*>(data);

                // Object that manages the raw buffer.
                eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->max_size);
                // Object that serializes the data.
                eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
                        data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
                        eprosima::fastcdr::CdrVersion::XCDRv1 : eprosima::fastcdr::CdrVersion::XCDRv2);
                payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
            #if FASTCDR_VERSION_MAJOR > 1
                ser.set_encoding_flag(
                    data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
                    eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR  :
                    eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2);
            #endif // FASTCDR_VERSION_MAJOR > 1

                try
                {
                    // Serialize encapsulation
                    ser.serialize_encapsulation();
                    // Serialize the object.
                    ser << *p_type;
            #if FASTCDR_VERSION_MAJOR > 1
                    ser.set_dds_cdr_options({0,0});
            #else
                    ser.setDDSCdrOptions(0);
            #endif // FASTCDR_VERSION_MAJOR > 1
                }
                catch (eprosima::fastcdr::exception::Exception& /*exception*/)
                {
                    return false;
                }

                // Get the serialized length
            #if FASTCDR_VERSION_MAJOR == 1
                payload->length = static_cast<uint32_t>(ser.getSerializedDataLength());
            #else
                payload->length = static_cast<uint32_t>(ser.get_serialized_data_length());
            #endif // FASTCDR_VERSION_MAJOR == 1
                return true;
            }

            bool Image_PubSubType::deserialize(
                    SerializedPayload_t* payload,
                    void* data)
            {
                try
                {
                    // Convert DATA to pointer of your type
                    Image_* p_type = static_cast<Image_*>(data);

                    // Object that manages the raw buffer.
                    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->length);

                    // Object that deserializes the data.
                    eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN
            #if FASTCDR_VERSION_MAJOR == 1
                            , eprosima::fastcdr::Cdr::CdrType::DDS_CDR
            #endif // FASTCDR_VERSION_MAJOR == 1
                            );

                    // Deserialize encapsulation.
                    deser.read_encapsulation();
                    payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

                    // Deserialize the object.
                    deser >> *p_type;
                }
                catch (eprosima::fastcdr::exception::Exception& /*exception*/)
                {
                    return false;
                }

                return true;
            }

            std::function<uint32_t()> Image_PubSubType::getSerializedSizeProvider(
                    void* data,
                    DataRepresentationId_t data_representation)
            {
                return [data, data_representation]() -> uint32_t
                       {
            #if FASTCDR_VERSION_MAJOR == 1
                           static_cast<void>(data_representation);
                           return static_cast<uint32_t>(type::getCdrSerializedSize(*static_cast<Image_*>(data))) +
                                  4u /*encapsulation*/;
            #else
                           try
                           {
                               eprosima::fastcdr::CdrSizeCalculator calculator(
                                   data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
                                   eprosima::fastcdr::CdrVersion::XCDRv1 :eprosima::fastcdr::CdrVersion::XCDRv2);
                               size_t current_alignment {0};
                               return static_cast<uint32_t>(calculator.calculate_serialized_size(
                                           *static_cast<Image_*>(data), current_alignment)) +
                                       4u /*encapsulation*/;
                           }
                           catch (eprosima::fastcdr::exception::Exception& /*exception*/)
                           {
                               return 0;
                           }
            #endif // FASTCDR_VERSION_MAJOR == 1
                       };
            }

            void* Image_PubSubType::createData()
            {
                return reinterpret_cast<void*>(new Image_());
            }

            void Image_PubSubType::deleteData(
                    void* data)
            {
                delete(reinterpret_cast<Image_*>(data));
            }

            bool Image_PubSubType::getKey(
                    void* data,
                    InstanceHandle_t* handle,
                    bool force_md5)
            {
                if (!m_isGetKeyDefined)
                {
                    return false;
                }

                Image_* p_type = static_cast<Image_*>(data);

                // Object that manages the raw buffer.
                eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(m_keyBuffer),
                        sensor_msgs_msg_dds__Image__max_key_cdr_typesize);

                // Object that serializes the data.
                eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS, eprosima::fastcdr::CdrVersion::XCDRv1);
            #if FASTCDR_VERSION_MAJOR == 1
                p_type->serializeKey(ser);
            #else
                eprosima::fastcdr::serialize_key(ser, *p_type);
            #endif // FASTCDR_VERSION_MAJOR == 1
                if (force_md5 || sensor_msgs_msg_dds__Image__max_key_cdr_typesize > 16)
                {
                    m_md5.init();
            #if FASTCDR_VERSION_MAJOR == 1
                    m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.getSerializedDataLength()));
            #else
                    m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.get_serialized_data_length()));
            #endif // FASTCDR_VERSION_MAJOR == 1
                    m_md5.finalize();
                    for (uint8_t i = 0; i < 16; ++i)
                    {
                        handle->value[i] = m_md5.digest[i];
                    }
                }
                else
                {
                    for (uint8_t i = 0; i < 16; ++i)
                    {
                        handle->value[i] = m_keyBuffer[i];
                    }
                }
                return true;
            }


        } //End of namespace dds_


    } //End of namespace msg


} //End of namespace sensor_msgs

