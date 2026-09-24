#include "SubmapContext.hpp"

#include <algorithm>
#include <utility>

using namespace Config::Actions;

CSubmapContext CSubmapContext::snapshot() {
    return *this;
}

bool CSubmapContext::contains(const std::string& submap) const {
    return find(submap) != std::nullopt;
}

bool CSubmapContext::contains(const WSubmap& submap) const {
    return m_submaps.contains(submap);
}

std::optional<WSubmap> CSubmapContext::find(const std::string& submap) const {
    const auto MATCH = std::ranges::find_if(m_submaps, [submap](const auto& s) { return s->name() == submap; });

    if (MATCH == m_submaps.end())
        return std::nullopt;

    return *MATCH;
}

std::optional<WSubmap> CSubmapContext::find(const WSubmap& submap) const {
    const auto MATCH = m_submaps.find(submap);

    if (MATCH == m_submaps.end())
        return std::nullopt;

    return *MATCH;
}

bool CSubmapContext::empty() const {
    return m_submaps.empty();
}

void CSubmapContext::add(WSubmap&& submap) {
    m_submaps.emplace(std::move(submap));
}

void CSubmapContext::remove(const std::string& submap) {
    std::erase_if(m_submaps, [submap](const auto& s) { return s->name() == submap; });
}

void CSubmapContext::remove(const WSubmap& submap) {
    m_submaps.erase(submap);
}

void CSubmapContext::toggle(WSubmap&& submap) {
    const size_t HAS_REMOVED = m_submaps.erase(submap);

    if (HAS_REMOVED)
        return;

    add(std::move(submap));
}

void CSubmapContext::reset() {
    m_submaps.clear();
}

const SubmapList& CSubmapContext::submaps() const {
    return m_submaps;
}
