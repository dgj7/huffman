package com.dg.jht.build;

import com.dg.jht.pojo.AbstractNode;
import com.dg.jht.pojo.HuffmanTree;
import com.dg.jht.pojo.SymbolNode;
import com.dg.jht.pojo.WeightNode;
import com.dg.jht.util.HuffNodeComparator;
import com.dg.jht.util.MessageRepository;
import org.apache.log4j.Logger;

import java.util.*;

/**
 * Build {@link HuffmanTree}s.
 */
public class HuffmanTreeBuilder {
    private final Logger logger = Logger.getLogger(HuffmanTreeBuilder.class);
    private final MessageRepository messageRepository = new MessageRepository();

    /**
     * Create a new {@link HuffmanTreeBuilder}.
     */
    public HuffmanTree build(final String input) {
        if (input.isEmpty()) {
            return build(new HashMap<>());
        } else {
            Map<String, Long> frequencyMap = (new FrequencyAnalyzer(input)).generateFrequencyMap();
            return build(frequencyMap);
        }
    }

    /**
     * Build a {@link HuffmanTree} from the given frequency map.
     */
    public HuffmanTree build(final Map<String, Long> frequencyMap) {
        if (frequencyMap.isEmpty()) {
            return new HuffmanTree(new WeightNode(null, null));
        }

        if (frequencyMap.size() == 1) {
            final String key = frequencyMap.entrySet().iterator().next().getKey();
            final char symbol = key.charAt(0);
            final Long frequency = frequencyMap.get(key);
            frequencyMap.put(String.valueOf(incrementChar(symbol)), frequency + 1);
        }

        AbstractNode root = buildNodes(frequencyMap);
        return new HuffmanTree(root);
    }

    /**
     * Build a {@link HuffmanTree} from the given frequency map.
     */
    private AbstractNode buildNodes(Map<String, Long> frequencyMap) {
        List<AbstractNode> nodes = new LinkedList<AbstractNode>();
        for (String symbol : frequencyMap.keySet()) {
            Long frequency = frequencyMap.get(symbol);
            AbstractNode node = new SymbolNode(symbol, frequency);
            nodes.add(node);
        }

        while (nodes.size() > 1) {
            Collections.sort(nodes, new HuffNodeComparator());
            logger.trace(messageRepository.buildNodesMessage(nodes));
            AbstractNode firstNode = nodes.remove(0);
            AbstractNode secondNode = nodes.remove(0);
            AbstractNode combinedNode = new WeightNode(firstNode, secondNode);
            nodes.add(combinedNode);
        }
        logger.trace(messageRepository.buildNodesMessage(nodes));
        return nodes.get(0);
    }

    /**
     * Generate the 'next' char/byte for instances where we need a dummy value.
     */
    private char incrementChar(final char input) {
        if (input == Byte.MAX_VALUE) {
            return (char) Byte.MIN_VALUE;
        } else {
            return (char) (input + 1);
        }
    }
}
