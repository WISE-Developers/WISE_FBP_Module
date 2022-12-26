package ca.wise.serialize;

import java.util.Optional;

import com.google.protobuf.Message;

/**
 * The interface that the base class of classes that will
 * be serialized using Google Protocol Buffers must
 * inherit from.
 *
 * @param <T> This should be the class that is inheriting
 * from ISerializeProto.
 */
public interface ISerializeProto<T extends ISerializeProto<T>> {

	/**
	 * Create, then serialize the class to its equivalent
	 * protobuf class.
	 * @return The protobuf class.
	 */
	Message serialize(SerializeProtoOptions options);
	
	/**
	 * Deserialize the class from its equivalent protobuf
	 * class.
	 * @param proto The protobuf message to deserialize.
	 * @return The object that was just deserialized, which
	 * may be itself or an object of a derived class.
	 */
	T deserialize(Message proto);
	
	/**
	 * Does the object need to be saved.
	 * @return True if the object needs saved, false if the
	 * object is up to date, or empty if the object doesn't
	 * track its state.
	 */
	Optional<Boolean> isDirty();
}
