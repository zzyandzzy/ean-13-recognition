package main;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

/**
 * @author intent <a>zzy.main@gmail.com</a>
 * @date 2021/4/13 09:25
 * @since 1.0
 */
public class Test {

	public static void main(String[] args) {
		Set<String> set = generate(9, 4, 4);
		System.out.println(set.size());
		Iterator<String> iterator = set.iterator();
		while (iterator.hasNext()) {
			String s = iterator.next();
			int currentContinueCountBit = 1;
			char currentBit = '0';
			StringBuilder sb = new StringBuilder("{");
			for (int i = 1; i < s.length(); i++) {
				if (s.charAt(i) != currentBit) {
					sb.append(currentContinueCountBit).append(",");
					currentContinueCountBit = 1;
					currentBit = s.charAt(i);
				} else {
					currentContinueCountBit++;
				}
			}
			sb.append(currentContinueCountBit);
			sb.append("},");
			System.out.println(sb.toString());
		}
	}

	public static Set<String> generate(int bitLength, int continueBit, int continueCountBit) {
		int length = (1 << bitLength) - 1;
		Set<String> set = new HashSet<>(length);
		for (int i = 0; i < length; i++) {
			String code = Integer.toBinaryString(i);
			if (code.length() != bitLength) {
				StringBuilder sb = new StringBuilder();
				for (int j = 0; j < bitLength - code.length(); j++) {
					sb.append("0");
				}
				sb.append(code);
				set.add(sb.toString());
			} else {
				set.add(code);
			}
		}
		// 过滤掉开头不为0结尾不为1和连续字符大于continueBit的字符串
		Iterator<String> iterator = set.iterator();
		while (iterator.hasNext()) {
			String s = iterator.next();
			if (s.charAt(0) != '0' || s.charAt(s.length() - 1) != '1') {
				iterator.remove();
				continue;
			}
			int currentContinueBit = 1;
			int maxContinueBit = currentContinueBit;
			char currentBit = '0';
			// 连续字符大于continueBit的字符串
			for (int i = 1; i < s.length(); i++) {
				if (s.charAt(i) == currentBit) {
					currentContinueBit++;
				} else {
					maxContinueBit = Math.max(maxContinueBit, currentContinueBit);
					currentContinueBit = 1;
					currentBit = s.charAt(i);
				}
			}
			maxContinueBit = Math.max(maxContinueBit, currentContinueBit);
			if (maxContinueBit > continueBit) {
				iterator.remove();
			}
		}
		// 过滤掉连续字符次数不等于continueCountBit的字符串
		iterator = set.iterator();
		while (iterator.hasNext()) {
			String s = iterator.next();
			int currentContinueCountBit = 1;
			char currentBit = '0';
			for (int i = 1; i < s.length(); i++) {
				if (s.charAt(i) != currentBit) {
					currentContinueCountBit++;
					currentBit = s.charAt(i);
				}
			}
			if (currentContinueCountBit != continueCountBit) {
				iterator.remove();
			}
		}
		return set;
	}
}
