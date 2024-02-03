package com.dg.jht;

import java.util.List;

import org.apache.log4j.Logger;

import com.dg.jht.build.HuffmanTreeBuilder;
import com.dg.jht.exc.HuffmanDecodingException;
import com.dg.jht.exc.HuffmanEncodingException;
import com.dg.jht.pojo.HuffmanTree;
import com.dg.jht.util.MessageRepository;

/**
 * Main driver file, for testing only.
 */
public class Main
{
	private static final HuffmanTreeBuilder builder = new HuffmanTreeBuilder();
	private static final Logger logger = Logger.getLogger(Main.class);
	private static final MessageRepository messageRepository = new MessageRepository();
	
	/**
	 * Main program entry point.
	 * 
	 * @param args
	 * @throws HuffmanEncodingException
	 * @throws HuffmanDecodingException
	 */
	public static void main(String []args) throws HuffmanEncodingException, HuffmanDecodingException
	{
		final String value;
		if (args.length == 2 && args[0].equals("-i")) {
			value = args[1];
		} else {
			throw new IllegalArgumentException("bad input args");
		}

		logger.info(String.format("input:   [%s]", value));
		
		HuffmanTree tree = builder.build(value);
		//logger.info(String.format("built huffman tree."));
		
		List<Boolean> encoded = tree.encode(value);
		logger.info(String.format("encoded: [%s]",messageRepository.getBitsAsString(encoded)));
		
		String decoded = tree.decode(encoded);
		logger.info(String.format("decoded: [%s]",decoded));
	}
}