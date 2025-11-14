package com.dg.jht.e2e;

import com.dg.jht.build.HuffmanTreeBuilder;
import com.dg.jht.exc.HuffmanDecodingException;
import com.dg.jht.exc.HuffmanEncodingException;
import com.dg.jht.pojo.HuffmanTree;
import com.dg.jht.util.MessageRepository;
import org.junit.Assert;
import org.junit.Ignore;
import org.junit.Test;

import java.util.List;

/**
 * End-to-end test for huffman tree build, encode, and decode.
 */
public class EndToEndTest {
    @Test
    public final void testEmptyString() throws HuffmanEncodingException, HuffmanDecodingException {
        final String input = "";

        final HuffmanTree tree = new HuffmanTreeBuilder().build(input);

        List<Boolean> encoded = tree.encode(input);
        Assert.assertEquals("", new MessageRepository().getBitsAsString(encoded));

        String decoded = tree.decode(encoded);
        Assert.assertEquals("", decoded);
    }

    @Ignore// todo: fix this test
    @Test
    public final void testSingleCharacter() throws HuffmanEncodingException, HuffmanDecodingException {
        final String input = "f";

        final HuffmanTree tree = new HuffmanTreeBuilder().build(input);

        List<Boolean> encoded = tree.encode(input);
        Assert.assertEquals("0", new MessageRepository().getBitsAsString(encoded));

        String decoded = tree.decode(encoded);
        Assert.assertEquals("f", decoded);
    }

    @Ignore// todo: fix this test
    @Test
    public final void testTwoBytesSame() throws HuffmanEncodingException, HuffmanDecodingException {
        final String input = "aa";

        final HuffmanTree tree = new HuffmanTreeBuilder().build(input);

        List<Boolean> encoded = tree.encode(input);
        Assert.assertEquals("00", new MessageRepository().getBitsAsString(encoded));

        String decoded = tree.decode(encoded);
        Assert.assertEquals("aa", decoded);
    }

    @Test
    public final void testTwoBytesDiff() throws HuffmanEncodingException, HuffmanDecodingException {
        final String input = "ab";

        final HuffmanTree tree = new HuffmanTreeBuilder().build(input);

        List<Boolean> encoded = tree.encode(input);
        Assert.assertEquals("01", new MessageRepository().getBitsAsString(encoded));

        String decoded = tree.decode(encoded);
        Assert.assertEquals("ab", decoded);
    }

    @Test
    public final void testShortString() throws HuffmanEncodingException, HuffmanDecodingException {
        final String input = "abcaba";

        final HuffmanTree tree = new HuffmanTreeBuilder().build(input);

        List<Boolean> encoded = tree.encode(input);
        Assert.assertEquals("011100110", new MessageRepository().getBitsAsString(encoded));

        String decoded = tree.decode(encoded);
        Assert.assertEquals("abcaba", decoded);
    }

    @Test
    public void testMainCase() throws HuffmanEncodingException, HuffmanDecodingException {
        final String input = "this is a sample input string. its text is being used to test the huffman coding tree.";

        final HuffmanTree tree = new HuffmanTreeBuilder().build(input);

        List<Boolean> encoded = tree.encode(input);
        Assert.assertEquals("100101110000011110000011111010111100110101010010101110100011011110000111010111100010011100110001100000011110110110010111000100001111100110110100110011100000111101101011010000111101101111100000111011100111111000101011110011010011001111001011111011111011111000010000100001001101010111111011011010101100110000111101101111000110011011101110010", new MessageRepository().getBitsAsString(encoded));

        String decoded = tree.decode(encoded);
        Assert.assertEquals("this is a sample input string. its text is being used to test the huffman coding tree.", decoded);
    }
}
